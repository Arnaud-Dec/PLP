import ast 
import astpretty 
code = """ 
def somme(a, b): 
    return a + b 
""" 
# Parser le code en AST 
arbre = ast.parse(code) 
# # Afficher l'AST avec indentation 
astpretty.pprint(arbre, indent=4)