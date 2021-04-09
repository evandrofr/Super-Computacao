import os
import io
import sys
import pprint
from grading_tools import TestConfiguration, ProgramTest, CheckOutputMixin, CheckStderrMixin, CheckMultiCorePerformance
from colorama import Fore


def compila_programa(ext, nome, flags, nvcc=False):
    compilador = 'g++'
    if nvcc:
        compilador = 'nvcc'
    arquivos = ' '.join([arq for arq in os.listdir('.') if arq.split('.')[-1] == ext])
    ret = os.system(f'{compilador} {arquivos} -O3 {flags} -o {nome} 2>/dev/null  > /dev/null')
    if ret != 0 :
        raise IOError(f'Erro de compilação em {nome}!')

def green(s):
    return Fore.GREEN + str(s) + Fore.RESET

def red(s):
    return Fore.RED + str(s) + Fore.RESET

def test_result(b):
    if b:
        return green(b)
    else:
        return red(b)

class BaseMMS:
    def parse_input(self, inp):
        lines = inp.split('\n')
        N, M = [int(i) for i in lines[0].split()]
        values = [int(i) for i in lines[1].split()]
        return N, M, values
    
    def parse_output(self, out, M):
        lines = out.split('\n')
        if len(lines) < M+1:
            print(f'Menos de {M+1} linhas detectadas na saída. É necessário uma linha por pessoa. Linhas vazias não contam.')
            return -1, []
            
        mms = int(lines[0])
        objects_person = [[] for _ in range(M)]
        
        for i in range(1, M+1):
            objects_person[i-1].extend([int(o) for o in lines[i].split()])

        return mms, objects_person
    
    def calc_mms(self, values, objects_person):
        min_mms = sum(values)
        person = None
        for i in range(len(objects_person)):
            i_mms = sum([values[o] for o in objects_person[i]])
            if i_mms < min_mms:
                min_mms = i_mms
                person = i
        return min_mms, person

    def objects_person_from_aloc(self, aloc, M):
        objects_person = [[] for _ in range(M)]
        for i, o in enumerate(aloc):
            objects_person[o].append(i)
        
        return objects_person
    
    def test_solucao_final_valida(self, test, stdout, stderr):
        N, M, values = self.parse_input(test.input)
        mms_out, objects_person = self.parse_output(stdout, M)
        return mms_out == self.calc_mms(values, objects_person)[0]


class TesteBuscaLocal(ProgramTest, BaseMMS):
    def test_roda_iter_vezes(self, test, stdout, stderr):
        N, M, values = self.parse_input(test.input)
        return len(stderr.split('\n')) == int(test.environ['ITER'])

    def test_solucao_final_eh_melhore_e_valida(self, test, stdout, stderr):
        N, M, values = self.parse_input(test.input)
        max_val = 0
        for sol in stderr.split('\n'):
            val, *aloc = [int(i) for i in sol.split()]

            if val > max_val:
                max_val = val
            
        mms_out, objects_person_out = self.parse_output(stdout, M)
        mms_out_recalc, _ = self.calc_mms(values, objects_person_out)
        return max_val == mms_out and mms_out == mms_out_recalc
        
    def test_toda_solucao_valida(self, test, stdout, stderr):
        N, M, values = self.parse_input(test.input)
        for sol in stderr.split('\n'):
            val, *aloc = [int(i) for i in sol.split()]

            objects_person = self.objects_person_from_aloc(aloc, M)
            min_mms, person = self.calc_mms(values, objects_person)
            
            if min_mms != val:
                print('Erro no cálculo do MMS:', sol)
                print('Calculado:', min_mms)
                return False

        return True
    
    def test_toda_solucao_sem_troca(self, test, stdout, stderr):
        N, M, values = self.parse_input(test.input)
        for sol in stderr.split('\n'):
            val, *aloc = [int(i) for i in sol.split()]
            if len(aloc) != N:
                print(f'Vetor de alocação tem menos que {N} objetos')
                return False
            sol_objects_person = self.objects_person_from_aloc(aloc, M)
            sol_min_mms, sol_person = self.calc_mms(values, sol_objects_person)
            
            for i in range(N):
                for j in range(N):
                    if i == j: continue
                    aloc[i], old_aloc_i = aloc[j], aloc[i]
                    objects_person = self.objects_person_from_aloc(aloc, M)
                    swap_min_mms, swap_person = self.calc_mms(values, objects_person)
                    
                    if swap_min_mms > sol_min_mms:
                        print('Doação de', i, 'para', j, 'possível')
                        print('Alocação antiga:', sol_objects_person)
                        print('Alocação nova:', objects_person)
                        print('Novo MMS', swap_min_mms)
                        return False
                    
                    aloc[i], aloc[j] = old_aloc_i, aloc[i]
                    
        return True


class TesteExaustivo(ProgramTest, BaseMMS, CheckStderrMixin):
    def test_MMS_minimo(self, test, stdout, stderr):
        N, M, values = self.parse_input(test.input)
        mms_out, _ = self.parse_output(stdout, M)
        mms_esperado, _ = self.parse_output(test.output, M)

        return mms_out == mms_esperado


class TesteHeuristico(ProgramTest, CheckOutputMixin):
    pass


def testa_heuristico():
    os.chdir('heuristico')
    compila_programa('cpp', 'heuristico', '')
    tests = TestConfiguration.from_pattern('.', 'in*.txt', 'out*txt')
    tester = TesteHeuristico('./heuristico', tests)
    res = tester.main()
    os.chdir('..')
    return res

def testa_busca_local_sequencial():
    os.chdir('busca-local')
    compila_programa('cpp', 'local', '')
    testes_basicos = TestConfiguration.from_pattern('.', 'in*.txt', 'out*txt', environ={'DEBUG': '1', 'ITER': '10'})
    tester = TesteBuscaLocal('./local', testes_basicos)
    res = tester.main()
    os.chdir('..')
    return res

def testa_busca_exaustiva():
    os.chdir('busca-global')
    compila_programa('cpp', 'global', '')
    testes_basicos = TestConfiguration.from_pattern('.', 'in*.txt', 'out*txt', 'err*txt', environ={'DEBUG': '1'})
    tester = TesteExaustivo('./global', testes_basicos)
    res = tester.main()
    os.chdir('..')
    return res

def testa_busca_local_omp():
    return False

def testa_busca_local_gpu():
    return False

if __name__ == "__main__":

    ignorar = io.StringIO()

    testesD = {
        'heuristico': ('Heuristico (sequencial)', testa_heuristico),
        'local': ('Busca local (sequencial)', testa_busca_local_sequencial),
        'global': ('Busca exaustiva (sequencial)', testa_busca_exaustiva),
        #'local-paralela': ('Busca local (paralela)', testa_busca_local_omp),
        #'local-gpu': ('Busca local (GPU)', testa_busca_local_gpu)
    }

    if len(sys.argv) > 1:
        tst = sys.argv[1]
        if tst in testesD:
            tst = testesD[tst]
            print(tst[0], ':', test_result(tst[1]()))
            sys.exit(0)

    print('Testes disponíveis:')
    pprint.pprint(testesD)



