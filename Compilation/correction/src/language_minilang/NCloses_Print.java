/* This file was generated by SableCC ( http://sablecc.org ). */

package language_minilang;

public class NCloses_Print
    extends NCloses {

  private final int line;
  private final int pos;
  private final N$1 e$1;
  private final NE eE;

  @Override
  public int getLine() {
    return this.line;
  }

  @Override
  public int getPos() {
    return this.pos;
  }

  @Override
  public String getText() {
    return null;
  }

  @Override
  public void apply(Walker walker) {
    walker.inCloses_Print(this);
    walker.caseCloses_Print(this);
    walker.outCloses_Print(this);
  }

  @Override
  public void applyOnChildren(Walker walker) {
    this.e$1.apply(walker);
    this.eE.apply(walker);
  }

  NCloses_Print(int line, int pos, N$1 p$1, NE pE) {
    this.line = line;
    this.pos = pos;
    this.e$1 = p$1;
    this.eE = pE;
  }

  @Override
  public Type getType() {
    return Type.T_Closes_Print;
  }

  @Override
  public ProductionType getProductionType() {
    return ProductionType.T_Closes;
  }

  @Override
  InternalType getInternalType() {
    return InternalType.T_Closes_Print;
  }

  public NE get_E() {
    return this.eE;
  }

  N$1 internalGet$1() {
    return this.e$1;
  }

  NE internalGetE() {
    return this.eE;
  }
}