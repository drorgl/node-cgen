	{
			
		function aggregate(arr){
			var result = [];
			if (typeof arr === "string"){
				return arr;
			}
			
			if (arr == null){
				return "";
			}
			
			for (var i = 0; i < arr.length;i++){
				if (Object.prototype.toString.call( arr[i] ) === '[object Array]' ) {
					result.push(aggregate(arr[i]));
				}else{
					result.push(arr[i]);
				}
			}
			
			return result.join("");
		}
			
	function collect(head, tail, n) {
	   var k = (n === undefined ? 0 : n);
	   var result = [];
	   if (head !== null) {
		  result.push(head);
	   }
	   for (var i in tail) {
		  result.push(tail[i][k]);
	   }
	   return result;
	}

	}

	start 
	   = pp:(ProgramPart)* {
       return pp;
		//return pp.map(function(p){return p[3];});
	   }
	   
	
	   
	/************ WhiteSpace and Comments ************/

	WhiteSpace = [ \t\f]
	LineTerminator = [\n\r]
	LineTerminatorSeq = "\n" / "\r\n" / "\r"
	SourceCharacter = .
	
    ___ = space: (WhiteSpace / LineTerminatorSeq / Comment)+ {
	   return {
		type: 'comment',
		comment: space
		};
	   }


	__ =
	   space: (WhiteSpace / LineTerminatorSeq / Comment / Directive)* {
	   return {
		type: 'comment',
		comment: space
		};
	   }

	_ =
	   space:(WhiteSpace / MultiLineCommentOneLine / SingleLineComment)* {
	   return {
		type: 'comment',
		comment: space
		};
	   }

	MultiLineComment =
	   "/*" comment:(!"*/" SourceCharacter)* "*/" {
       	 return comment.map(function (f) {return f.toString().substring(1);}).join("").trim();
	   }

	MultiLineCommentOneLine = 
	   "/*" comment:(!("*/" / LineTerminator) SourceCharacter)* "*/" {
		return comment.map(function (f) {return f.toString().substring(1);}).join("").trim();
	   }

	SingleLineComment =
	   "//" comment:(!LineTerminator SourceCharacter)* { 
	   	 return comment.map(function (f) {return f.toString().substring(1);}).join("").trim();
	   }

	Comment =
	   MultiLineComment /
	   SingleLineComment

	/*Whitespace end*/
	
	MultiLineDirective = 
		x: (((!(([\\] LineTerminatorSeq) / LineTerminatorSeq) SourceCharacter)* [\\] LineTerminatorSeq)+ SingleLineDirective) {
        	return  x;
        }
	
	SingleLineDirective = 
		(!LineTerminatorSeq SourceCharacter)+
		
	
	Directive = 
	 ("#" directive:(MultiLineDirective / SingleLineDirective)+  )
	 {
	  var dagg = aggregate(directive);
	  var part1 = dagg.indexOf(" ");
		 return {
          type: 'directive',
		  directive : dagg.substring(0,part1),
		  parameter : dagg.substring(part1)
		 };
	   }
	
	
	/************ Identifiers ************/

	IdentifierStart = [_A-Za-z]
	IdentifierRest  = [_A-Za-z0-9_]

	FullIdentifier = 
	   !(KeyWord !IdentifierRest)
	   start:IdentifierStart rest:IdentifierRest* {
		return start + rest.join("");
	   }

	OperatorName = 
	   "operator" __? op:Operator 
	   
	TemplatedIdentifier = 
		destructor:("~")? id:FullIdentifier template:("<" (__? (Type /[0-9]+) __? ","?)+ ">" __?)? {
			return id + ((template != null) ? template.join("") : "");
		}

	Identifier = 
	   prefix:(TemplatedIdentifier? __? "::" __?)* name:(OperatorName / TemplatedIdentifier) {
		return {
			prefix: prefix,
			name : name
		}
	   }
	   
	IncludeFilename = [_A-Za-z0-9./]*
	DirectiveIdentifier = [a-zA-Z0-9./_]*

	VariableValue = [_A-Za-z0-9./-]*
	   
	/*   Identifier end*/

	/************ Keywords and Operators ************/

	KeyWord = 
	   "and" / "and_eq" / "alignas" / "alignof" / "asm" / "auto" / 
	   "bitand" / "bitor" / "bool" / "break" / "case" / "catch" / "char" / 
	   "char16_t" / "char32_t" / "class" / "compl" / "const" / "constexpr" / 
	   "const_cast" / "continue" / "decltype" / "default" / "delete" / "double" / 
	   "dynamic_cast" / "else" / "enum" / "explicit" / "export" / "extern" / 
	   "false" / "float" / "for" / "friend" / "goto" / "if" / "inline" / "int" / 
	   "long" / "mutable" / "namespace" / "new" / "noexcept" / "not" / "not_eq" /
	   "nullptr" / "operator" / "or" / "or_eq" / "private" / "protected" / "public" / 
	   "register" / "reinterpret_cast" / "return" / "short" / "signed" / "sizeof" / 
	   "static" / "static_assert" / "static_cast" / "struct" / "switch" / "template" / 
	   "this" / "thread_local" / "throw" / "true" / "try" / "typedef" / "typeid" / 
	   "typename" / "union" / "unsigned" / "using" / "virtual" / "void" / "volatile" / 
	   "wchar_t" / "while" / "xor" / "xor_eq" / "__attribute__" / "__may_alias__"

	Operator = "+=" / "-=" / "*=" / "/=" / "%=" / ">>=" / "<<=" / "&=" / "^=" / "|=" / 
	   "--" / "++" / "()" / "[]" / "." / "->"  / "new" /
	   ".*" / "->*" / 
	   "<<" / ">>" / "<=" / ">=" /
	   "<" / ">" / 
	   "==" / "!=" / 
	   "&&" / "||" / 
	   "&" / "|" / "^" / "=" /
	   "," / 
	   "+" / "-" / "!" / "~" / "*" /
	   "*" / "%" / "/" / BasicTypeName

	/*Operators*/


	/***************** Types ******************/

	BasicTypeName = "bool" / "int" / "string" / "long long" / "long" / "char" / "float" / "double" / "void" / "short"
	
	UnsignedTypeName = "char" / "int" / "short"

	BasicType = type:BasicTypeName !IdentifierRest { return type; }

	TypePrefixes = 
		prefix:("unsigned" / "explicit" / "inline" / "static" / "const" / "struct" / "virtual" / "CV_EXPORTS_W_MAP" / "CV_EXPORTS_W_SIMPLE" / "CV_EXPORTS_W" / "CV_WRAP" /  "CV_EXPORTS" / "CV_OUT" / "FLANN_DEPRECATED" / "CV_PROP_RW" / "CV_PROP" / "CV_IN_OUT" / "friend" / "__attribute__" / "((__may_alias__))" / "CV_INLINE" / "__host__" / "__device__" / "volatile"){
			return prefix;
		}

	TemplatePrefixes =
		"typename" / "class"
	
	TypeName = 
		name:(
			   Identifier /
			   BasicType / 
			   "template"
		    )
			
	Type = 
	   name: (("unsigned" (__ UnsignedTypeName)?)  / (
			prefixes:(TypePrefixes __?)*
			destructor: ("~" __?)?
			name:TypeName
			prefixes:(__? TypePrefixes)*
		) )
	   opref:(__? "&")?
	   template: (__? "<" (__? (TemplatePrefixes __?)* __? (Type) __? ","?)* ">" )?
	   ref:(__? "&")?
	   ptr:(__? "*")* 
	   constptr : (__? "const*")? 
	   constref : (__? "const&")? {
		return {
			prefixes : (Object.prototype.toString.call(name) === "[object array]") ? name.map(function(f){return (f != null) ? f[0] : null}) : name,
			destructor : (Object.prototype.toString.call(name) === "[object array]") ? name.map(function(f){return (f != null) ? f[1] : null}) : name,
			name : name,
			opref : opref,
			template : template,
			ref : ref,
			ptr : ptr
		};
	   }
	   

	TypedefFunctionDeclaration = 
		extern:(ExternC __)?
		"typedef" __ (TemplatePrefixes __?)* __? from:Type __ "(" __? "*"? __? id:(Identifier __?)? ")" __? template:("<" ((__? "class")? __? Type __? ","?)+ ">" __?)? "(" parameters:(__? ((Type __ ParameterDirective?) / ("...") / ("void")) __? ","?)* ")" __? ";" {
			return {
				type : 'typedef',
				from: from,
				id : id
			};
		}
	   
	TypedefDirective =
		extern:(ExternC __)?
		"typedef" __ (TemplatePrefixes __?)* __? from:Type __ prefixes:(TypePrefixes __?)* id:Identifier __ ";" {
			return {
				type : 'typedef',
				from: from,
				id : id
			};
		}
		
	TypedefClassDirective = 
		"typedef" __ ClassDirective
	
	Extern = 
		"extern" __
		
	ExternC = 
		Extern "\"C\""
	   
	ExternCDirective = 
		ExternC __? "{" body:(__? ProgramPart)* __? "}" ";"? {
			return {
				type:'externC',
				body: body.map(function(f){return f[1]})
			};
		}
	   
	NamespaceDirective = 
		"namespace" __ id:Identifier __? "{" body:(__? ProgramPart)* __? "}" ";"? {
			return {
				type:'namespace',
				id: id,
				body: body.map(function(f){return f[1]})
			};
		}
	   
	AssignmentSection = 
		(AssignmentOperator __?)*
		( 
		("<" __? AssignmentSection+ __? ">") /
		("(" __? AssignmentSimplePart __? Operator __? AssignmentSimplePart __? ")" __? "?" __? AssignmentSimplePart __? ":" __? AssignmentSimplePart) /
		("(" (__? AssignmentSection __? ","?)* __? ")") / 
		("[" (__? AssignmentSection __? ","?)* __? "]") / 
		(AssignmentPart __? "(" (__? AssignmentDirective __? ","?)* __? ")") /
		(AssignmentPart __? "(" __? ")") /
		AssignmentPart / 
		AssignmentLiteral 
		
		)
		
	AssignmentLiteral = 
		"'" (!"'" SourceCharacter)* "'" / 
		"\"" (!"\"" SourceCharacter)* "\"" 
		
	
	AssignmentSimplePart = 
		part:[a-zA-Z0-9\-_.]+ {
			return aggregate(part);
		}	
	
	AssignmentPart = 
		part:(__? [a-zA-Z0-9\-_.:]+)+ {
			return aggregate(part);
		}
		
	AssignmentOperator = 
		"~" / "+" / "-" / "&" / "<<" / "|" / "*" / "/"
	   
	AssignmentDirective = 
		("=" __? first:AssignmentSection more:(__? AssignmentSection)*) /
		("CV_DEFAULT" __? "(" __? first:AssignmentSection more:(__? AssignmentSection)* ")")
		{
			return first + more.join("");
		}
	   
	ParameterDirective = 
		key:(FullIdentifier) (__? "[" __? VariableValue? __? "]")? value:(__? AssignmentDirective)? {
			debugger;
			return {
				key: key,
				sign: (value != null) ? value[1] : null,
				value : (value != null) ? aggregate(value[3]) : null
			};
		}
	   
	EnumDirective = 
		("typedef" __)?
		"enum" id:(__ FullIdentifier)? __? "{" values:(__? ParameterDirective __? ","?)* __? "}"
		(__? FullIdentifier)?
		";"? {
			return {
				type: 'enum',
				id: id,
				values: values.map(function(i){return i[1];})
			};
		}
	   
	UsingDirective = 
		"using" (__? "namespace")? __? Identifier __? ";"
	   
	Accessibility = 
		("public" / "private" / "protected")
	   
	ClassDirective=
		template:("template" template: (__? "<" __? (__? (TemplatePrefixes __?)* __? (Type __? ParameterDirective? __? AssignmentDirective?) __? ","?)* ">" ) __?)?
		friend:("friend")? __?
		type:("class" / "struct" ) __? 
		prefixes:(TypePrefixes __?)* __? 
		id:Identifier 
		idTypes:(__? "<" __? ( __? ((Type __? ParameterDirective?) / "true") __? ","?)* ">" )?
		bases:(__? ":" (__? (Accessibility __?)? (TypePrefixes __?)* __? Identifier __? ","?)*)? 
		parts:(__? "{" (__? ClassParts)* __?  "}")? __? ";" {
			return {
				template : template,
				type: type,
				prefixes : prefixes.map(function(p){return p[0];}),
				id : id,
				bases: (bases != null) ? {
					access: bases[3],
					id : bases[5]
				} : null,
				parts: (parts != null) ? parts[2].map(function(p){return p[1];}) : null
				
			}
		}
	

	MethodPrototypeDefinition = 
		isTemplate: ("template" __? "<" ((__? TemplatePrefixes __?)* __? Identifier __? ","?)* ">" __?)?
		type:(Type __)? destructor:"~"? id:"(" "*"? __? (Identifier __?)? ")" template:("<" ((__? "class")? __? Type __? ","?)+ ">" __?)? "(" parameters:(__? ((Type __ ParameterDirective?) / ("...") / ("void")) __? ","?)* ")" {
			return {
				type:'method',
				returnType:(type != null) ? type[0] : null,
				destructor: destructor,
				id: (id != null) ? id[0] : null,
				template: template,
				parameters: parameters.map(function(m){return {
					type: m[1],
					id: m[3]
				};})
			}
		}
		
	
	OperatorPrototype =
	    ret:(Type __?)? "operator" __ id:(Type __?)? template:("<" ((__? "class")? __? Type __? ","?)+ ">" __?)? "(" parameters:(__? ((Type __ ParameterDirective?) / ("...") / ("void") / MethodPrototypeDefinition) __? ","?)* ")"
	   
	MethodPrototype = 
		isTemplate: ("template" __? "<" ((__? (TemplatePrefixes / BasicTypeName) __?)* __? Identifier __? ","?)* ">" __?)*
		type:(Type __)? destructor:"~"? id:(Identifier __?)? template:("<" ((__? "class")? __? Type __? ","?)+ ">" __?)? "(" parameters:(__? ((Type __ (ParameterDirective / (AssignmentDirective))?) / ("...") / ("void") / MethodPrototypeDefinition) __? ","?)* ")" {
			return {
				type:'method',
				returnType:(type != null) ? type[0] : null,
				destructor: destructor,
				id: (id != null) ? id[0] : null,
				template: template,
				parameters: parameters.map(function(m){return {
					type: m[1],
					id: m[3]
				};})
			}
		}
	   
	Block = 
		"{" (!"}" (Block / SourceCharacter))* "}"
		
	MethodCall = 
		Identifier __? "(" (__? AssignmentSection __? ","?)* ")"
	   
	MethodImplementation = 
		mp: (MethodPrototype / MethodPrototypeDefinition / OperatorPrototype) (__? ":" (__? MethodCall __? ","?)+)? __? "const"? (__? Block)? ";"? {
			return mp;
		}
	   
	MethodDefinition = 
		 mp:(MethodPrototype / MethodPrototypeDefinition / OperatorPrototype) __? "const"? __? "throw()"? __? ("=" __? "0")? ";" {
			return mp;
		 }
		 
	TemplateMethodDefinition = 
		template:"template<>" __? mp:MethodDefinition{
			return {
				template: template,
				method: mp
			};
		}
		
    
        
	FieldDefinition = 
		extern:Extern?
		fieldType:Type __? id:(Identifier (__? "[" __? AssignmentSection? __? "]")? value:(__? AssignmentDirective)? __? ","? __?)+ __? ";" {
			return {
				type: 'field',
				fieldType: fieldType,
				id: id
			};
		}
	   
	ClassParts = 
		(Accessibility ":") / 
		MethodDefinition /
		MethodImplementation /
		EnumDirective / 
		FieldDefinition / 
		UsingDirective /
		TypedefDirective / 
		TypedefFunctionDeclaration /
		ClassDirective / 
		TypedefClassDirective
		
	ProgramPart = 
		TypedefDirective /
		TypedefFunctionDeclaration /
		NamespaceDirective /
		ExternCDirective / 
		EnumDirective / 
		FieldDefinition / 
		ClassDirective / 
		TypedefClassDirective /
		MethodDefinition /
		MethodImplementation / 
		TemplateMethodDefinition /
		UsingDirective / 
        Directive / 
		___
		
		