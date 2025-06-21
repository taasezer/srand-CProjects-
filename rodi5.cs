using System;

class Araba
{
    public string Marka { get; set; }
    public string Model { get; set; }

    public void BilgileriGoster()
    {
        Console.WriteLine($"Araba Markası: {Marka}, Modeli: {Model}");
    }
}

class Program
{
    static void Main(string[] args)
    {
        Araba araba = new Araba();
        araba.Marka = "Toyota";
        araba.Model = "Corolla";
        araba.BilgileriGoster();
    }
}