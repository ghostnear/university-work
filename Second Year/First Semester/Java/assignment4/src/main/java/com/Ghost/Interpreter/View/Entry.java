package com.Ghost.Interpreter.View;

import com.Ghost.Interpreter.Controller.*;
import com.Ghost.Interpreter.Repository.*;

public class Entry {
    public static void main(String[] args) {
        // The main method in Lab5.pdf is an abomination that should be banished from this existence.
        Interpreter interpreter = new Interpreter(new ProgramState());
        TextView view = new TextView(interpreter, new HardcodedProgramDB());
        view.show();
    }
}