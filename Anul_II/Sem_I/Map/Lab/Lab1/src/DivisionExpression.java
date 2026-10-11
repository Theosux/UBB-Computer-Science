public class DivisionExpression extends ComplexExpression {

    public DivisionExpression(NumarComplex[] args) {
        super(args);
    }

    @Override
    protected NumarComplex executeOneOperation(NumarComplex t1, NumarComplex t2) {
        return t1.impartire(t2);
    }
}