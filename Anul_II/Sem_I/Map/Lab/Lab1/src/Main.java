public class Main {
    public static void main(String[] args) {
        ExpressionParser parser = new CommandLineExpressionParser();
        try {
            ComplexExpression expresie = parser.parse(args);
            System.out.println(expresie.execute());
        } catch (IllegalArgumentException e) {
            System.out.println("expresie invalida: " + e.getMessage());
        } catch (ArithmeticException e) {
            System.out.println("eroare: " + e.getMessage());
        }
    }
}