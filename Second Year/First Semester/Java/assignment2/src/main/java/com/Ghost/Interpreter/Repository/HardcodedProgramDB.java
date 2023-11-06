package com.Ghost.Interpreter.Repository;

import java.util.ArrayList;

import com.Ghost.Interpreter.Models.*;
import com.Ghost.Interpreter.Models.Expressions.*;
import com.Ghost.Interpreter.Models.Statements.*;
import com.Ghost.Interpreter.Models.Types.*;
import com.Ghost.Interpreter.Models.Values.*;

public class HardcodedProgramDB {
    ArrayList<IStatement> statements;

    public HardcodedProgramDB() {
        statements = new ArrayList<IStatement>();

        // First example from Lab3.pdf
        statements.add(
            new CompositeStatement(
                new VariableDeclareStatement(
                    "v",
                    new IntegerType()
                ),
                new CompositeStatement(
                    new AssignStatement(
                        "v",
                        new ValueExpression(
                            new IntegerValue(2)
                        )
                    ),
                    new PrintStatement(
                        new VariableExpression("v")
                    )
                )
            )
        );

        // Second example from Lab3.pdf
        statements.add(
            new CompositeStatement(
                new VariableDeclareStatement(
                    "a",
                    new IntegerType()
                ),
                new CompositeStatement(
                    new VariableDeclareStatement(
                        "b",
                        new IntegerType()
                    ),
                    new CompositeStatement(
                        new AssignStatement(
                            "a",
                            new BinaryExpression(
                                "+",
                                new ValueExpression(
                                    new IntegerValue(2)
                                ),
                                new BinaryExpression(
                                    "*",
                                    new ValueExpression(
                                        new IntegerValue(3)
                                    ),
                                    new ValueExpression(
                                        new IntegerValue(5)
                                    )
                                )
                            )
                        ),
                        new CompositeStatement(
                            new AssignStatement(
                                "b",
                                new BinaryExpression(
                                    "+",
                                    new VariableExpression("a"),
                                    new ValueExpression(
                                        new IntegerValue(1)
                                    )
                                )
                            ),
                            new PrintStatement(
                                new VariableExpression("b")
                            )
                        )
                    )
                )
            )
        );

        // Third and last example from Lab3.pdf
        statements.add(
            new CompositeStatement(
                new VariableDeclareStatement(
                    "a",
                    new BooleanType()
                ),
                new CompositeStatement(
                    new VariableDeclareStatement(
                        "v",
                        new IntegerType()
                    ),
                    new CompositeStatement(
                        new AssignStatement(
                            "a",
                            new ValueExpression(new BooleanValue(true))),
                    new CompositeStatement(
                        new IfStatement(
                            new VariableExpression("a"),
                            new AssignStatement(
                                "v",
                                new ValueExpression(new IntegerValue(2))
                            ),
                            new AssignStatement(
                                "v",
                                new ValueExpression(new IntegerValue(3))
                            )
                        ),
                        new PrintStatement(new VariableExpression("v")))
                    )
                )
            )
        );

        // Bonus example with NOPs
        statements.add(
            new CompositeStatement(
                new NOPStatement(),
                new CompositeStatement(
                    new VariableDeclareStatement(
                        "d", 
                        new BooleanType()
                    ),
                    new IfStatement(
                        new BinaryExpression(
                            "==",
                            new VariableExpression("d"),
                            new ValueExpression(new BooleanValue(true))
                        ),
                        new PrintStatement(new ValueExpression(new IntegerValue(7))),
                        null
                    )
                )
            )
        );
    }

    public ArrayList<IStatement> getAll() {
        return statements;
    }

    public Integer size(){
        return statements.size();
    }

    public IStatement get(Integer index){
        return statements.get(index);
    }
}
