import sys

member_functions = ["std::string getString()",
		    "U evaluate()",
		   ]
#"void resolve()"

def main(args):
	if(len(args) != 2):
		print("Usage: python generateAST <output directory>")
	else:
		types = {"Binary" : "Expr* left, TokenImpl<T> op, Expr* right",
			 "Grouping" : "Expr* expression",
			 "Literal" : "T value",
			 "Unary": "TokenImpl<T> op, Expr* right"}
		
		out_dir = args[1]
		base_name = "Expr"
		defineAST(out_dir, base_name, types)

def defineAST(out_dir, base_name, types):
	f = open(base_name.lower()+".hpp", "w")

	#include guards
	f.write("#ifndef "+base_name.upper()+"_H\n")
	f.write("#define "+base_name.upper()+"_H\n\n")

	f.write("#include <vector>\n\n")
	f.write("#include \"token.hpp\"\n\n")

	'''
	#initial declaration of classes
	fields = []
	for key in types:
		fields.append(types[key].split(','))
		f.write("class "+key+";\n")
	'''

	#base class 
	f.write("\nclass "+base_name+"{\n")
	f.write("public:\n")
	f.write("\tvirtual ~"+base_name+"() {}\n")

	#TODO: figure out what to with pure virtual functions and template functions
	for func in member_functions:
		if "U " not in func:
			f.write("\tvirtual "+func+" const = 0;\n")
	
	f.write("};\n")
	f.write("\n")

	#child classes
	for key, value in types.items():
		if "T " in value or "<T>" in value:
			f.write("template <class T>\n")
		fields = value.split(', ')
		f.write("class "+key+": public "+base_name+" {\n")
		f.write("public:\n")
		for field in fields:
			f.write("\t"+field+";\n")
		f.write("\n")
	
		f.write("\t"+key+"("+value+") : ")
		tab_len = len(key+"("+value+") : ")

		#constructor
		for index, field in enumerate(fields):
			var_name = field.split(" ")[1]
			if index != 0:
				f.write("\t"+" "*tab_len)
			f.write(var_name+"("+var_name+")")
			if index != len(fields)-1:
				f.write(",")
			else:
				f.write(" {}")
			f.write("\n")
		f.write("\n")

		#member function declaration
		for func in member_functions:
			#deal with template functions
			if "U " in func:
				f.write("\ttemplate <class U>\n")
				f.write("\t"+func+";\n")
			else:
				f.write("\t"+func+" const override;\n")
		
		f.write("};\n")
	f.write("\n")
	#end include guard
	f.write("#endif")

if __name__ == "__main__":
	main(sys.argv)
