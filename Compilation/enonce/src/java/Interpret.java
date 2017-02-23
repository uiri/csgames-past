
import java.util.*;
import java.io.*;
import language_mpire.*;

public class Interpret extends Walker {

	public static void main(String[] args)
		throws Exception {

		Reader in;

		if(args.length > 0) {
			in = new FileReader(args[0]);
		}
		else {
			in = new InputStreamReader(System.in);
		}

		Node syntaxTree = new Parser(in).parse();
		syntaxTree.apply(new Interpret());
	}

}
