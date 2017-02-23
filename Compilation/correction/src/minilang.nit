import minilang_test_parser

# An naive recursive stack-based interpreter of the minilang language.
class Interpretor
	super Visitor

	# A stack of numeric values
	var stack = new Array[Int]

	# A stack of boolean values
	var bstack = new Array[Bool]

	# The current values assigned to each variable
	var vars = new HashMap[String, Int]

	redef fun visit(n) do n.accept_minilang(self)
end

redef class Node
	# Execution of the node by the interpreter `v`
	fun accept_minilang(v: Interpretor) do visit_children(v)
end

redef class Nint
	redef fun accept_minilang(v) do v.stack.push(text.to_i)
end

redef class Nchar
	redef fun accept_minilang(v) do v.stack.push(text[1].code_point)
end

redef class Ns_assign
	redef fun accept_minilang(v) do
		super
		v.vars[n_id.text] = v.stack.pop
	end
end

redef class Ns_print
	redef fun accept_minilang(v) do
		super
		printn v.stack.pop
	end
end
redef class Ns_print_byte
	redef fun accept_minilang(v) do
		super
		printn v.stack.pop.code_point
	end
end
redef class Ns_print_str
	redef fun accept_minilang(v) do
		var text = n_str.text
		text = text.substring(1, text.length-2)
		printn text
	end
end
redef class Ns_println
	redef fun accept_minilang(v) do
		print ""
	end
end
redef class Ns_if
	redef fun accept_minilang(v) do
		v.enter_visit(n_c)
		if v.bstack.pop then
			v.enter_visit(n_then)
		else
			var nelse = n_else
			if nelse != null then v.enter_visit(nelse)
		end
	end
end
redef class Ns_while
	redef fun accept_minilang(v) do
		loop
			v.enter_visit(n_c)
			if not v.bstack.pop then break
			v.enter_visit(n_s)
		end
	end
end


redef class Nc_and
	redef fun accept_minilang(v) do
		super
		var b1 = v.bstack.pop
		var b2 = v.bstack.pop
		v.bstack.push(b1 and b2)
	end
end

redef class Nc_or
	redef fun accept_minilang(v) do
		super
		var b1 = v.bstack.pop
		var b2 = v.bstack.pop
		v.bstack.push(b1 or b2)
	end
end

redef class Nc_not
	redef fun accept_minilang(v) do
		super
		v.bstack.push(not v.bstack.pop)
	end
end

redef class Nc_cp
	redef fun accept_minilang(v) do
		v.bstack.push(true) # base result
		super
		v.stack.pop # discard value
	end
end

redef class Ncp
	redef fun accept_minilang(v) do
		super
		var right = v.stack.pop
		var left = v.stack.pop
		var before = v.bstack.pop
		var result = eval(left, right) and before
		v.bstack.push result
		v.stack.push right
	end

	fun eval(l, r: Int): Bool is abstract
end

redef class Ncp_eq
	redef fun eval(l, r) do return l == r
end

redef class Ncp_ne
	redef fun eval(l, r) do return l != r
end

redef class Ncp_lt
	redef fun eval(l, r) do return l < r
end

redef class Ncp_le
	redef fun eval(l, r) do return l <= r
end

redef class Ncp_gt
	redef fun eval(l, r) do return l > r
end

redef class Ncp_ge
	redef fun eval(l, r) do return l >= r
end


class Ne_op
	super Ne
	redef fun accept_minilang(v) do
		super
		var right = v.stack.pop
		var left = v.stack.pop
		var result = eval(left, right)
		v.stack.push(result)
	end

	fun eval(l, r: Int): Int is abstract
end

redef class Ne_add
	super Ne_op
	redef fun eval(l, r) do return l + r
end
redef class Ne_sub
	super Ne_op
	redef fun eval(l, r) do return l - r
end
redef class Ne_mul
	super Ne_op
	redef fun eval(l, r) do return l * r
end
redef class Ne_div
	super Ne_op
	redef fun eval(l, r) do return l / r
end
redef class Ne_neg
	redef fun accept_minilang(v) do
		super
		v.stack.push(-v.stack.pop)
	end
end
redef class Ne_var
	redef fun accept_minilang(v) do
		v.stack.push v.vars[n_id.text]
	end
end
redef class Ne_read
	redef fun accept_minilang(v) do
		var t = stdin.read_line
		if t.is_int then
			v.stack.push(t.to_i)
		else
			v.stack.push -1
		end
	end
end
redef class Ne_read_byte
	redef fun accept_minilang(v) do
		var t = stdin.read_byte
		if t == null then
			v.stack.push -1
		else
			v.stack.push(t.to_i)
		end
	end
end

if args.is_empty then
	print "usage: minilang source.m"
	return
end

var f = args.first.to_path
var c = f.read_all
var le = f.last_error
if le != null then
	print le.message
	return
end

var l = new Lexer_minilang(c)
var p = new Parser_minilang
p.tokens.add_all l.lex
var n = p.parse
if n isa NError then
	print "{n.position or else "?"}: {n.message}"
	return
end

var v = new Interpretor 
v.enter_visit(n)
