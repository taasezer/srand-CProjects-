using System;

class Program
{
    static void Main(string[] args)
    {
        string[] meyveler = { "Elma", "Muz", "Çilek", "Portakal" };

        Console.WriteLine("Meyve Listesi:");
        foreach (var meyve in meyveler)
        {
            Console.WriteLine(meyve);
        }
    }
}