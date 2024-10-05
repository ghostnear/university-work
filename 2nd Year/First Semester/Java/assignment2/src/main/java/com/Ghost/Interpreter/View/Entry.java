package com.Ghost.Interpreter.View;

import com.Ghost.Interpreter.Controller.*;
import com.Ghost.Interpreter.Repository.*;

public class Entry {
    public static void main(String[] args) {
        ProgramState programState = new ProgramState();
        Interpreter interpreter = new Interpreter(programState);
        View view = new View(interpreter, new HardcodedProgramDB());
        view.run();
    }
}