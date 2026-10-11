public class MultiplicationExpression extends ComplexExpression {

    public MultiplicationExpression(NumarComplex[] args) {
        super(args);
    }

    @Override
    protected NumarComplex executeOneOperation(NumarComplex t1, NumarComplex t2) {
        return t1.inmultire(t2);
    }
}