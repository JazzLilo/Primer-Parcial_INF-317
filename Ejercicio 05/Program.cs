using System.Collections;
using System;
using System.Threading;

class Program
{
    static void Series(object state)  
    {
        var val = (Tuple<long, long>)state;  
        long x = val.Item1;  
        long y = val.Item2;  

        long result1 = (x * x) + 1;
        long result2 = 2 * y;

        Console.WriteLine(result1);  
        Console.WriteLine(result2); 
    }

    static void Main()  
    {
        int ini = 1;     
        int fin = 10000;     

        for (int i = ini; i <= fin / 2; i++)  
        {
            long a = i;  
            long b = i; 
            ThreadPool.QueueUserWorkItem(Series, new Tuple<long, long>(a, b));  
            Thread.Sleep(1);
        }

        Console.ReadKey(); 
    }
}

