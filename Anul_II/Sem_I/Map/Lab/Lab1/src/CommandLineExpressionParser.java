// citeste expresia, verifica
// pe pozitii pare avem nr pe cele impare operatori

public class CommandLineExpressionParser implements ExpressionParser {

    @Override
    public ComplexExpression parse(String[] args) {
        // avem nevoie de macar n1 op n2
        if (args.length < 3 || args.length % 2 == 0) {
            throw new IllegalArgumentException("Numar gresit de argumente");
        }

        //acelasi operator
        Operation op = parseOperation(args[1]);
        for (int i = 3; i < args.length; i += 2) {
            if (!args[i].equals(args[1])) {
                throw new IllegalArgumentException("Operatorii trebuie sa fie la fel");
            }
        }

        //Nr pe pozitiile 0, 2, 4 etc
        NumarComplex[] numere = new NumarComplex[(args.length + 1) / 2];
        for (int i = 0; i < numere.length; i++) {
            numere[i] = parseNumarComplex(args[2 * i]);
        }

        return ExpressionFactory.getInstance().createExpression(op, numere);
    }

    private NumarComplex parseNumarComplex(String token) {
        // fara i => doar parte reala
        if (!token.endsWith("i")) {
            return new NumarComplex(Double.parseDouble(token), 0);
        }

        // scot "i" si "*" de la final: "5-6*i" -> "5-6", "-2+i" -> "-2+"
        String text = token.substring(0, token.length() - 1);
        if (text.endsWith("*")) {
            text = text.substring(0, text.length() - 1);
        }

        // semnul dintre partea reala si cea imaginara (ultimul + sau -, dar nu primul caracter)
        int poz = Math.max(text.lastIndexOf('+'), text.lastIndexOf('-'));
        String real = "0";
        String imaginar = text;
        if (poz > 0) {
            real = text.substring(0, poz);
            imaginar = text.substring(poz);
        }

        // "i" singur inseamna 1*i
        if (imaginar.equals("") || imaginar.equals("+")) {
            imaginar = "1";
        } else if (imaginar.equals("-")) {
            imaginar = "-1";
        }

        // Double.parseDouble arunca NumberFormatException daca textul nu e numar
        return new NumarComplex(Double.parseDouble(real), Double.parseDouble(imaginar));
    }

    private Operation parseOperation(String token) {
        switch(token) {
            case "+":
                return Operation.ADDITION;
            case "-":
                return Operation.SUBTRACTION;
            case "*":
                return Operation.MULTIPLICATION;
            case "/":
                return Operation.DIVISION;
            default:
                throw new IllegalArgumentException("Operator necunoscut: " + token);
        }
    }
}