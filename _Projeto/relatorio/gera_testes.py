import os
import random

def gera_testes(n_testes=10, test_name="25", x_persons=25, x_objects=150, N_min_value=1, N_max_value=50, lock_person=True, lock_objects = False):
    path = os.getcwd() + "/testes/" + test_name
    try:
        for file in os.listdir(path):
            os.remove(f"{path}/{file}")
    except OSError:
        pass
    try:
        os.mkdir(path)
    except OSError:
        pass
    
    random.seed(42)
    for i in range(n_testes):
        if lock_person == False:
            M = 1 + x_persons * i # persons
        else:
            M = x_persons
        if lock_objects == False:
            N = M + 75 + x_objects * i # objects
        else: 
            N = x_objects  
        f= open(f"/{path}/in{i}.txt","w+")
        f.write(f"{N} {M}\n")
        for i in range(N):
            n_value = random.randint(N_min_value, N_max_value)
            f.write("%d " % (n_value))
        f.close()

if __name__ == "__main__":
    gera_testes()