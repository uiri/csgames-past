package language_minilang;

import java.util.*;
import java.io.*;

public class Interpret extends Walker {

	private Stack<Object> interpret_stack = new Stack<Object>();

	public void caseInt(NInt node) {
		interpret_stack.push(node.getText());
	}

	public void caseStr(NStr node) {
		interpret_stack.push(node.getText());
	}

	public void caseStmt_Print(NStmt_Print node) {
		node.get_Expr().apply(this);
		System.out.println(this.interpret_stack.pop());
	}

	public void caseStmt_Stmts(NStmt_Stmts node) {
		defaultCase(node);
	}

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
		System.out.println();
		syntaxTree.apply(new Interpret());
	}

}

