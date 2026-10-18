import java.text.DecimalFormat;

public class NumarComplex {
    private double real;
    private double imaginar;

    public NumarComplex(double real, double imaginar) {
        this.real = real;
        this.imaginar = imaginar;
    }

    public double getReal() {
        return real;
    }

    public double getImaginar() {
        return imaginar;
    }

    //(a+bi)+(c+di)=(a+c)+(b+d)i
    public NumarComplex adunare(NumarComplex nr) {
        return new NumarComplex(real + nr.real, imaginar + nr.imaginar);
    }

    //(a+bi)-(c+di)=(a-c)+(b-d)i
    public NumarComplex scadere(NumarComplex nr) {
        return new NumarComplex(real - nr.real, imaginar - nr.imaginar);
    }

    //(a+bi)(c+di)=(ac-bd)+(ad+bc)i
    public NumarComplex inmultire(NumarComplex nr) {
        return new NumarComplex(real * nr.real - imaginar * nr.imaginar, real * nr.imaginar + imaginar * nr.real);
    }

    //(a+bi)/(c+di)=[(ac+bd)+(bc-ad)i]/(c^2+d^2)
    public NumarComplex impartire(NumarComplex nr) {
        double numitor = nr.real * nr.real + nr.imaginar * nr.imaginar;
        if (numitor == 0) {
            throw new ArithmeticException("impartire la zero");
        }
        return new NumarComplex((real * nr.real + imaginar * nr.imaginar)/numitor, (imaginar * nr.real - real * nr.imaginar)/numitor);
    }

    @Override
    public String toString() {
        if (imaginar == 0) {
            return formateaza(real);
        }
        if (imaginar > 0) {
            return formateaza(real) + "+" + formateaza(imaginar) + "*i";
        }
        return formateaza(real) + "-" + formateaza(-imaginar) + "*i";
    }

    //1.0 devine 1 si 0.1111... devine 0.11
    private String formateaza(double x) {
        DecimalFormat df = new DecimalFormat("0.##");
        return df.format(x);
    }
}
