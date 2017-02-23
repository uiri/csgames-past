/* This file was generated by SableCC (http://www.sablecc.org/). */

package org.sablecc.objectmacro.intermediate.syntax3.node;

import org.sablecc.objectmacro.intermediate.syntax3.analysis.*;

@SuppressWarnings("nls")
public final class TEolKeyword extends Token
{
    public TEolKeyword()
    {
        super.setText("eol");
    }

    public TEolKeyword(int line, int pos)
    {
        super.setText("eol");
        setLine(line);
        setPos(pos);
    }

    @Override
    public Object clone()
    {
      return new TEolKeyword(getLine(), getPos());
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseTEolKeyword(this);
    }

    @Override
    public void setText(@SuppressWarnings("unused") String text)
    {
        throw new RuntimeException("Cannot change TEolKeyword text.");
    }
}