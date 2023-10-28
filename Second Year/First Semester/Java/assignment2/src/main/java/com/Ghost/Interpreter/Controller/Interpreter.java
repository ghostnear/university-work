package com.Ghost.Interpreter.Controller;

import com.Ghost.Interpreter.Repository.*;

public class Interpreter {
    ProgramState programState;

    public Interpreter(ProgramState newProgramState) {
        this.programState = newProgramState;
    }
}
