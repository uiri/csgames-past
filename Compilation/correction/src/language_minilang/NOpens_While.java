/* This file was generated by SableCC ( http://sablecc.org ). */

package language_minilang;

public class NOpens_While
    extends NOpens {

  private final int line;
  private final int pos;
  private final N$8 e$8;
  private final NC eC;
  private final NOpens eOpens;

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
    walker.inOpens_While(this);
    walker.caseOpens_While(this);
    walker.outOpens_While(this);
  }

  @Override
  public void applyOnChildren(Walker walker) {
    this.e$8.apply(walker);
    this.eC.apply(walker);
    this.eOpens.apply(walker);
  }

  NOpens_While(int line, int pos, N$8 p$8, NC pC, NOpens pOpens) {
    this.line = line;
    this.pos = pos;
    this.e$8 = p$8;
    this.eC = pC;
    this.eOpens = pOpens;
  }

  @Override
  public Type getType() {
    return Type.T_Opens_While;
  }

  @Override
  public ProductionType getProductionType() {
    return ProductionType.T_Opens;
  }

  @Override
  InternalType getInternalType() {
    return InternalType.T_Opens_While;
  }

  public NC get_C() {
    return this.eC;
  }

  public NOpens get_Opens() {
    return this.eOpens;
  }

  N$8 internalGet$8() {
    return this.e$8;
  }

  NC internalGetC() {
    return this.eC;
  }

  NOpens internalGetOpens() {
    return this.eOpens;
  }
}