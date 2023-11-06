using System;

class Program
{
    public static double[] piArray;
    public static int numTerms = 10000000;

    static void Pi(object message)
    {
        int posicion = (int)message;
        double val = 1.0 / ((2.0 * posicion) + 1.0);
        piArray[posicion] = (posicion % 2 == 0) ? val : -val;
    }

    static void Main()
    {
        piArray = new double[numTerms];

        for (int i = 0; i < numTerms; i++)
        {
            ThreadPool.QueueUserWorkItem(Pi, i);
        }

        Thread.Sleep(3000);

        double sum = 0.0;
        for (int i = 0; i < numTerms; i++)
        {
            sum += piArray[i];
        }

        double pi = 4 * sum;

        Console.WriteLine("El valor de PI =  " + pi);
        Console.ReadKey();
    }
}
