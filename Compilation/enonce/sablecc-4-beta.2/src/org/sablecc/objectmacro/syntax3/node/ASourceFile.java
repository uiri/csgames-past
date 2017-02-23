/* This file was generated by SableCC (http://www.sablecc.org/). */

package org.sablecc.objectmacro.syntax3.node;

import java.util.*;
import org.sablecc.objectmacro.syntax3.analysis.*;

@SuppressWarnings("nls")
public final class ASourceFile extends PSourceFile
{
    private final LinkedList<PSourceFilePart> _parts_ = new LinkedList<PSourceFilePart>();

    public ASourceFile()
    {
        // Constructor
    }

    public ASourceFile(
        @SuppressWarnings("hiding") List<PSourceFilePart> _parts_)
    {
        // Constructor
        setParts(_parts_);

    }

    @Override
    public Object clone()
    {
        return new ASourceFile(
            cloneList(this._parts_));
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseASourceFile(this);
    }

    public LinkedList<PSourceFilePart> getParts()
    {
        return this._parts_;
    }

    public void setParts(List<PSourceFilePart> list)
    {
        this._parts_.clear();
        this._parts_.addAll(list);
        for(PSourceFilePart e : list)
        {
            if(e.parent() != null)
            {
                e.parent().removeChild(e);
            }

            e.parent(this);
        }
    }

    @Override
    public String toString()
    {
        return ""
            + toString(this._parts_);
    }

    @Override
    void removeChild(@SuppressWarnings("unused") Node child)
    {
        // Remove child
        if(this._parts_.remove(child))
        {
            return;
        }

        throw new RuntimeException("Not a child.");
    }

    @Override
    void replaceChild(@SuppressWarnings("unused") Node oldChild, @SuppressWarnings("unused") Node newChild)
    {
        // Replace child
        for(ListIterator<PSourceFilePart> i = this._parts_.listIterator(); i.hasNext();)
        {
            if(i.next() == oldChild)
            {
                if(newChild != null)
                {
                    i.set((PSourceFilePart) newChild);
                    newChild.parent(this);
                    oldChild.parent(null);
                    return;
                }

                i.remove();
                oldChild.parent(null);
                return;
            }
        }

        throw new RuntimeException("Not a child.");
    }
}