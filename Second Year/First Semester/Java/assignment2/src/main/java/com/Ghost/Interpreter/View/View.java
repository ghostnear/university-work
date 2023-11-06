package com.Ghost.Interpreter.View;

import java.util.Scanner;

import com.Ghost.Interpreter.Controller.*;
import com.Ghost.Interpreter.Exceptions.InterpreterException;
import com.Ghost.Interpreter.Repository.*;

public class View {
    Interpreter interpreter;
    HardcodedProgramDB programDB;
    Scanner inputScanner;

    enum MainMenuOptions {
        RUN_PROGRAM,
        VIEW_PROGRAM,
        EXIT,
        SIZE
    };

    public View(Interpreter newInterpreter, HardcodedProgramDB newProgramDB) {
        this.interpreter = newInterpreter;
        this.programDB = newProgramDB;
    }

    void run_program() throws InterpreterException {
        System.out.print("Input program (0.." + (programDB.size() - 1) + "): ");

        Integer program = inputScanner.nextInt();

        this.interpreter.reset_program_state();
        this.interpreter.load_program(this.programDB.get(program));
        this.interpreter.run_program(true);
    }

    void view_program() {
        System.out.print("Input program (0.." + (programDB.size() - 1) + "): ");

        Integer program = inputScanner.nextInt();

        System.out.println(programDB.get(program));
    }

    public void run() {
        inputScanner = new Scanner(System.in);

        MainMenuOptions option = MainMenuOptions.SIZE;
        while(option != MainMenuOptions.EXIT)
        {
            System.out.println("1. Run program");
            System.out.println("2. View program");
            System.out.println("3. Exit");
            System.out.print("Option: ");
            try {
                option = MainMenuOptions.values()[inputScanner.nextInt() - 1];
                switch(option) {
                    case RUN_PROGRAM:
                        run_program();
                        break;
                    case VIEW_PROGRAM:
                        view_program();
                        break;
                    case EXIT:
                        System.out.println("Exiting now...");
                        break;
                    default:
                        break;
                }
            }
            catch(InterpreterException e) {
                System.out.println(e);
            }
        }
    }
}
