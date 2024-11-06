import java.util.Scanner;

    public class BinomialDistribution {

        //factorial n! = n*(n-1)...2*1
        public static long factorial (int n) {
            if (n == 0) return 1;
            long res = 1;
            for (int i = 1; i <= n; i++) {
                res *= i;
            }
            return res;
        }
        //combination C(n, r) = n! / r!(n-r)!
        public static long combinations(int n,int k) {
            if (k == n || k == n ) return 1;
            return factorial(n) / (factorial(k) * factorial(n - k));
        }

     //binomial probability P(x:n,p) = nCx * p^x * (1-p)^(n-x)
        public static double binomialProbability (int n, int k, double p){
            return combinations(n, k) * Math.pow(p, k) * Math.pow(1 - p, n - k);
        }

        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);

            System.out.print("Enter number of white balls: ");
            int whiteBalls = scanner.nextInt();

            System.out.print("Enter number of black balls: ");
            int blackBalls = scanner.nextInt();

            System.out.print("Enter number of trials: ");
            int trials = scanner.nextInt();

            // The probability of drawing a black ball
            double probability = (double) blackBalls / (whiteBalls + blackBalls);

            System.out.println("The binomial distribution for ξ is Bi(" + trials + "; " + probability + ")");
            System.out.println("P(ξ = k) for k = 0 to " + trials + ":");

            // Compute and display probabilities for k = 0 to trials
            for (int k = 0; k <= trials; k++) {
                double probabilityK = binomialProbability(trials, k, probability);
                System.out.printf("P(ξ = %d) = %.3f%n", k, probabilityK);
            }

            scanner.close();
        }
 }