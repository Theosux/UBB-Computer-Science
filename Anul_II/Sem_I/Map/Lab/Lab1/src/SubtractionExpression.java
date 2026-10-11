public class SubtractionExpression extends ComplexExpression {

    public SubtractionExpression(NumarComplex[] args) {
        super(args);
    }

    @Override
    protected NumarComplex executeOneOperation(NumarComplex t1, NumarComplex t2) {
        return t1.scadere(t2);
    }
}