package com.Ghost.Interpreter.View;

import com.Ghost.Interpreter.Controller.Interpreter;
import com.Ghost.Interpreter.Repository.HardcodedProgramDB;
import javafx.stage.Stage;

public class GUIView extends IView {
    Stage window;

    public GUIView(Interpreter newInterpreter, HardcodedProgramDB newProgramDB, Stage mainWindow) {
        window = mainWindow;
        window.setTitle("Program Selection");
    }

    public void show() {
        window.show();
    }
}
