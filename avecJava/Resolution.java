public class Resolution
{
    private static double epsilon , maxIter;

    public Resolution()
    {
        epsilon = 0.0001;
        maxIter = 100;
    }
    public static double f(double x)
    {
        double fx;
        fx = Math.log(x) - 1;
        return (fx);
    }

    public static double fprime(double x)
    {
        double fprimex;
        fprimex = 1/x;
        return (fprimex);
    }

    public static double dichotomie(double a , double b)
    {
        double centre ;
        int i ;

        centre = a;
        i = 0;
        if(f(a)*f(b) >= 0)
        {
            System.out.println("Pas de solution entre a et b"  + f(a) + f(b));
        }
        else
        {
            for(i=0 ; i<maxIter ; i++)
            {
                centre = (a+b) / 2.0;
                if(Math.abs(f(centre)) < epsilon)
                {
                    break;
                }
                if(f(a)*f(centre) < 0)
                {
                    b = centre;
                }
                else
                {
                    a = centre;
                }
            }
        }
        System.out.println(">> dichotomie , nombre d'iteration : " + i);
        return (centre);
    }

    public static double newton(double a)
    {
        int i;
        double sn , sn1;

        i = 0;
        sn = a;
        for(i=0 ; i<maxIter ; i++)
        {
            if(Math.abs(fprime(a)) < 1e-14)
            {
                System.out.println("Derive nulle en " + a + " , essayer une valeur de depart si possible");
            }
            sn = a - (f(a)/fprime(a));
            if(Math.abs(sn-a) < epsilon)
            {
                a = sn;
                break;
            }
            a = sn;
        }
        System.out.println(">> newton , nombre d'iteration : " + i);
        return (a);
    }
    public static double rectangle(double a , double b , int subDivision)
    {
        double aire , large , i , tmp;

        if(a > b)
        {
            tmp = a;
            a = b;
            b = tmp;
        }
        aire = 0;
        large = 0;
        i = a;
        if(subDivision < 0)
        {
            System.out.println("la subdivision doit etre inferieur a 0");
            return (-1);
        }
        else
        {
            large = Math.abs((b-a) / subDivision);

            i += large;
            while(i <= b)
            {
                aire += large * f(i);
                i += large;
            }
        }

        System.out.println(">> rectangle : ");

        return (aire);
    }
    public static double trapeze(double a , double b , int subDivision)
    {
        double aire , large , tmp , sn , sn1;
        int iteration;

        if(a > b)
        {
            tmp = a;
            a = b;
            b = tmp;
        }
        
        iteration = 0;
        aire = 0;
        large = 0;
        if(subDivision < 0)
        {
            System.out.println("la subdivision ne doit pas etre inferieur a 0");
            return (-1);
        }
        else
        {
            sn = a;
            sn1 = a + large;
            large = (b-a)/subDivision;
            while(sn1<=b)
            {
                // aire trapeze
                aire += ((f(sn) + f(sn1)) * large) / 2;

                sn += large;
                sn1 += large;
                iteration++;
            }
        }
        System.out.println(">> trapeze : ");
        return (aire);
    }
    public static void main(String[] argument)
    {
        System.out.println(dichotomie(1 , 3));
        System.out.println(newton(1));
        System.out.println(trapeze(3 , 4.1 , 100));
        System.out.println(rectangle(3 , 4.1 , 100));
    }
};
