package com.Ghost.Interpreter.Models.Statements;

import com.Ghost.Interpreter.ADTs.Dictionary;
import com.Ghost.Interpreter.Exceptions.CheckingException;
import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Types.BooleanType;
import com.Ghost.Interpreter.Repository.ProgramState;

public class ConditionalAssignmentStatement implements IStatement {
    String name;
    IExpression condition, expression, elseExpression;

    public ConditionalAssignmentStatement(String id, IExpression condition, IExpression expression, IExpression elseExpression) {
        this.name = id;
        this.condition = condition;
        this.expression = expression;
        this.elseExpression = elseExpression;
    }

    public void execute(ProgramState state) throws InterpreterException {
        state.get_execution_stack().push(
            new IfStatement(
                this.condition,
                new AssignStatement(this.name, this.expression),
                new AssignStatement(this.name, this.elseExpression)
            )
        );
    }

    public String toString() {
        return name + " = " + condition.toString() + " ? " + expression.toString() + " : " + elseExpression.toString() + ";";
    }

    public Dictionary<String, IType> typeCheck(Dictionary<String, IType> typeEnvironment) throws InterpreterException {
        if(!typeEnvironment.has(this.name))
            throw new CheckingException("ConditionalAssignmentStatement: Variable is not defined!");

        if( !(typeEnvironment.get(this.name).equal(this.expression.typeCheck(typeEnvironment))) ||
            !(typeEnvironment.get(this.name).equal(this.elseExpression.typeCheck(typeEnvironment))))
            throw new CheckingException("ConditionalAssignmentStatement: Type of variable and type of expression do not match!");
        
        if(!(this.condition.typeCheck(typeEnvironment).equal(new BooleanType())))
            throw new CheckingException("ConditionalAssignmentStatement: Condition is not a boolean expression!");

        typeEnvironment.set(this.name, this.expression.typeCheck(typeEnvironment));

        return typeEnvironment;
    }
}
