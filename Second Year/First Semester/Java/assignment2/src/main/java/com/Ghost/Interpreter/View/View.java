package com.Ghost.Interpreter.View;

import java.util.Scanner;

import com.Ghost.Interpreter.Controller.*;
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

    void view_program() {
        System.out.print("Input program: ");

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
            option = MainMenuOptions.values()[inputScanner.nextInt() - 1];

            switch(option) {
                case RUN_PROGRAM:
                    System.out.println("Unimplemented yet...");
                    break;
                case VIEW_PROGRAM:
                    view_program();
                    break;
                case EXIT:
                    System.out.println("Exiting now...");
                    break;
                default:
                    System.out.println("Invalid option!");
                    break;
            }
        }
    }
}
