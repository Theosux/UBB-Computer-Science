// expresia: n1 op n2 op .. op nk
// clasa e abstracta, stie sa parcurga dar nu stie ce operatie sa faca, acolo vor interveni subclasele

public abstract class ComplexExpression {
    protected NumarComplex[] args;

    public ComplexExpression(NumarComplex[] args) {
        this.args = args;
    }

    public NumarComplex execute() {
        NumarComplex rezultat = args[0];
        for (int i = 1; i < args.length; i++) {
            rezultat = executeOneOperation(rezultat, args[i]);
        }
        return rezultat;
    }

    //operatia dintre doua numere
    protected abstract NumarComplex executeOneOperation(NumarComplex t1, NumarComplex t2);
}
