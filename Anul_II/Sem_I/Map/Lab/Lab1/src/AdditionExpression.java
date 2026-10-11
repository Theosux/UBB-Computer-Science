public class AdditionExpression extends ComplexExpression{

    public AdditionExpression(NumarComplex[] args) {
        super(args);
    }

    @Override
    protected NumarComplex executeOneOperation(NumarComplex t1, NumarComplex t2) {
        return t1.adunare(t2);
    }
}
