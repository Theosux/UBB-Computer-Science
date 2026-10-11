//Creeaza expresia potrivita pt o operatie (Factory)
//Exista o singura instanta (Singleton)

public class ExpressionFactory {
    private static ExpressionFactory instance;

    private ExpressionFactory() {
    }

    public static ExpressionFactory getInstance() {
        if (instance == null) {
            instance = new ExpressionFactory();
        }
        return instance;
    }

    public ComplexExpression createExpression(Operation op, NumarComplex[] args) {
        switch (op) {
            case ADDITION:
                return new AdditionExpression(args);
            case SUBTRACTION:
                return new SubtractionExpression(args);
            case MULTIPLICATION:
                return new MultiplicationExpression(args);
            default:
                return new DivisionExpression(args);
        }
    }
}
