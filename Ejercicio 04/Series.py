import multiprocessing
from multiprocessing import Pool

def Series(a, b):
    result1 = (a * a) + 1  
    result2 = 2 * b  
    return result1, result2

if __name__ == '__main__':
    ini = 1  
    fin = 10000  
    process = multiprocessing.cpu_count()
    pool = Pool()  
    result = pool.starmap(Series, [(x, x) for x in range(ini, fin + 1)])
    for x, y in result:
        print(x)
        print(y) 
