/* This file was generated by SableCC ( http://sablecc.org ). */

package language_minilang;

class S_33
    extends FinalState {

  static final S_33 instance = new S_33();

  private S_33() {
  }

  Token getToken(Lexer lexer) {
    String text = lexer.accept(0);
    int line = lexer.getAcceptLine();
    int pos = lexer.getAcceptPos();

    return new N$19(text, line, pos);
  }
}