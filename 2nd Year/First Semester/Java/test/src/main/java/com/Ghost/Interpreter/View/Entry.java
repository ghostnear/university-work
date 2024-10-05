package com.Ghost.Interpreter.View;

import com.Ghost.Interpreter.Controller.*;
import com.Ghost.Interpreter.Repository.*;

import javafx.application.Application;
import javafx.stage.Stage;

public class Entry extends Application {
    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage mainWindow) throws Exception {
        Interpreter interpreter = new Interpreter();
        IView view;
        // view = new TextView(interpreter, new HardcodedProgramDB());
        view = new GUIView(interpreter, new HardcodedProgramDB(), mainWindow);
        view.show();
    }
}