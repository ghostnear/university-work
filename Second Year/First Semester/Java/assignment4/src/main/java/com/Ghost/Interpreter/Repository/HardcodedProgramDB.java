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
                            new ArithmeticExpression(
                                "+",
                                new ValueExpression(
                                    new IntegerValue(2)
                                ),
                                new ArithmeticExpression(
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
                                new ArithmeticExpression(
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

        // File example from Lab5.pdf
        statements.add(
            new CompositeStatement(
                new VariableDeclareStatement("varf", new StringType()),
                new CompositeStatement(
                    new AssignStatement(
                        "varf",
                        new ValueExpression(new StringValue("test.in")) 
                    ),
                    new CompositeStatement(
                        new OpenReadFileStatement(new VariableExpression("varf")),
                        new CompositeStatement(
                            new VariableDeclareStatement("varc", new IntegerType()),
                            new CompositeStatement(
                                new ReadFromFileStatement(
                                    new VariableExpression("varf"),
                                    "varc"
                                ),
                                new CompositeStatement(
                                    new PrintStatement(new VariableExpression("varc")),
                                    new CompositeStatement(
                                        new ReadFromFileStatement(
                                            new VariableExpression("varf"),
                                            "varc"
                                        ),
                                        new CompositeStatement(
                                            new PrintStatement(new VariableExpression("varc")),
                                            new CloseReadFileStatement(new VariableExpression("varf"))
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        );

        // File example #1 from Lab7.pdf
        statements.add(
            new CompositeStatement(
                new VariableDeclareStatement(
                    "v", 
                    new RefferenceType(new IntegerType())
                ),
                new CompositeStatement(
                    new AllocateStatement(
                        "v",
                        new ValueExpression(new IntegerValue(20))
                    ),
                    new CompositeStatement(
                        new VariableDeclareStatement(
                            "a",
                            new RefferenceType(new RefferenceType(new IntegerType()))
                        ),
                        new CompositeStatement(
                            new AllocateStatement(
                                "a",
                                new VariableExpression("v")
                            ),
                            new CompositeStatement(
                                new PrintStatement(new VariableExpression("v")),
                                new PrintStatement(new VariableExpression("a"))
                            )
                        )
                    )
                )
            )  
        );
        
        // File example #2 from Lab7.pdf
        statements.add(
            new CompositeStatement(
                new VariableDeclareStatement(
                    "v", 
                    new RefferenceType(new IntegerType())
                ),
                new CompositeStatement(
                    new AllocateStatement(
                        "v",
                        new ValueExpression(new IntegerValue(20))
                    ),
                    new CompositeStatement(
                        new VariableDeclareStatement(
                            "a",
                            new RefferenceType(new RefferenceType(new IntegerType()))
                        ),
                        new CompositeStatement(
                            new AllocateStatement(
                                "a",
                                new VariableExpression("v")
                            ),
                            new CompositeStatement(
                                new PrintStatement(
                                    new ReadHeapExpression(new VariableExpression("v"))
                                ),
                                new PrintStatement(
                                    new ArithmeticExpression(
                                        "+",
                                        new ReadHeapExpression(new ReadHeapExpression(new VariableExpression("a"))),
                                        new ValueExpression(new IntegerValue(5))
                                    )
                                )
                            )
                        )
                    )
                )
            )  
        );

        // File example #3 from Lab7.pdf
        statements.add(
            new CompositeStatement(
                new VariableDeclareStatement(
                    "v", 
                    new RefferenceType(new IntegerType())
                ),
                new CompositeStatement(
                    new AllocateStatement(
                        "v",
                        new ValueExpression(new IntegerValue(20))
                    ),
                    new CompositeStatement(
                        new PrintStatement(
                            new ReadHeapExpression(new VariableExpression("v"))
                        ),
                        new CompositeStatement(
                            new WriteHeapStatement(
                                "v",
                                new ValueExpression(new IntegerValue(30))
                            ),
                            new PrintStatement(
                                new ArithmeticExpression(
                                    "+",
                                    new ReadHeapExpression(new VariableExpression("v")),
                                    new ValueExpression(new IntegerValue(5))
                                )
                            )
                        )
                    )
                )
            )  
        );
    
        // File example #4 from Lab7.pdf
        statements.add(
            new CompositeStatement(
                new VariableDeclareStatement(
                    "v", 
                    new RefferenceType(new IntegerType())
                ),
                new CompositeStatement(
                    new AllocateStatement(
                        "v",
                        new ValueExpression(new IntegerValue(20))
                    ),
                    new CompositeStatement(
                        new VariableDeclareStatement(
                            "a",
                            new RefferenceType(new RefferenceType(new IntegerType()))
                        ),
                        new CompositeStatement(
                            new AllocateStatement(
                                "a",
                                new VariableExpression("v")
                            ),
                            new CompositeStatement(
                                new PrintStatement(
                                    new ReadHeapExpression(new VariableExpression("v"))
                                ),
                                new CompositeStatement(
                                    new AllocateStatement(
                                        "v",
                                        new ValueExpression(new IntegerValue(30))
                                    ),
                                    new PrintStatement(
                                        new ReadHeapExpression(new ReadHeapExpression(new VariableExpression("a")))
                                    )
                                )
                            )
                        )
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
