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
    arquivos = ' '.join([arq for arq in os.listdir('.')
                         if arq.split('.')[-1] == ext])
    ret = os.system(
        f'{compilador} {arquivos} -O3 {flags} -o {nome} 2>/dev/null  > /dev/null')
    if ret != 0:
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
    return False


def testa_busca_exaustiva():
    return False


def testa_busca_local_omp():
    return False


def testa_busca_local_gpu():
    return False


if __name__ == "__main__":

    ignorar = io.StringIO()

    testesD = {
        'heuristico': ('Heuristico (sequencial)', testa_heuristico),
        # 'local': ('Busca local (sequencial)', testa_busca_local_sequencial),
        # 'global': ('Busca exaustiva (sequencial)', testa_busca_exaustiva),
        # 'local-paralela': ('Busca local (paralela)', testa_busca_local_omp),
        # 'local-gpu': ('Busca local (GPU)', testa_busca_local_gpu)
    }

    if len(sys.argv) > 1:
        tst = sys.argv[1]
        if tst in testesD:
            tst = testesD[tst]
            print(tst[0], ':', test_result(tst[1]()))
            sys.exit(0)

    print('Testes disponíveis:')
    pprint.pprint(testesD)
