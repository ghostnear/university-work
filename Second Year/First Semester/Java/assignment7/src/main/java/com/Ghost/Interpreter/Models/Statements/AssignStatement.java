package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.ADTs.Dictionary;
import com.Ghost.Interpreter.Exceptions.CheckingException;
import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Exceptions.Expressions.*;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Repository.ProgramState;

public class AssignStatement implements IStatement {
    String name;
    IExpression expression;

    public AssignStatement(String id, IExpression expression) {
        this.name = id;
        this.expression = expression;
    }

    public void execute(ProgramState state) throws InterpreterException {
        if(!state.get_symbol_table().has(this.name))
            throw new VariableUndefinedException();

        if(!(state.get_symbol_table().get(this.name).get_type().equal(this.expression.evaluate(state).get_type())))
            throw new TypeMismatchException();

        state.get_symbol_table().set(this.name, this.expression.evaluate(state));
    }

    public String toString() {
        return name + " = " + expression.toString() + ";";
    }

    public Dictionary<String, IType> typeCheck(Dictionary<String, IType> typeEnvironment) throws InterpreterException {
        if(!typeEnvironment.has(this.name))
            throw new CheckingException("AssignStatement: Variable is not defined!");

        if(!(typeEnvironment.get(this.name).equal(this.expression.typeCheck(typeEnvironment))))
            throw new CheckingException("AssignStatement: Type of variable and type of expression do not match!");

        return typeEnvironment;
    }
}
