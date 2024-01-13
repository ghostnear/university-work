package com.Ghost.Interpreter.View;

import java.util.ArrayList;

import com.Ghost.Interpreter.Controller.Interpreter;
import com.Ghost.Interpreter.Models.IStatement;
import com.Ghost.Interpreter.Repository.HardcodedProgramDB;

import javafx.geometry.Insets;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Separator;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class GUIView extends IView {
    Stage window;
    HardcodedProgramDB programRepository;
    Interpreter interpreter;

    TextField threadCountField;

    private void populateView()
    {
        threadCountField.setText(String.valueOf(interpreter.get_program_states().size()));
    }

    private Parent createSelectionContents()
    {
        VBox container = new VBox();
        container.setSpacing(15);
        HBox parent = new HBox();
        ArrayList<IStatement> programs = programRepository.getAll();
        for(int index = 0; index < programs.size(); index++)
        {
            Button button = new Button(programs.get(index).toString());
            button.setWrapText(true);
            button.setStyle("-fx-font-size: 15px;");
            final int finalIndex = index;
            button.onMouseClickedProperty().setValue((event) -> {
                try {
                    interpreter.load_program(programs.get(finalIndex));
                } catch (Exception e) {
                    e.printStackTrace();
                }
                window.setScene(new Scene(createProfilerComponents(), 960, 960));
                window.setTitle("Program Profiler");
                populateView();
            });
            button.setPrefWidth(960 / 3);
            button.setPrefHeight(960 / 3);
            parent.getChildren().add(button);

            if((index + 1) % 3 == 0)
            {
                container.getChildren().add(parent);
                parent = new HBox();
            }
        }
        container.getChildren().add(parent);

        Text instructionText = new Text("Press on any button to select a program.\nThis will open up a new window.");
        instructionText.setWrappingWidth(960 / 3);
        instructionText.setStyle("-fx-font-size: 15px;");
        instructionText.setTextAlignment(javafx.scene.text.TextAlignment.CENTER);
        parent.getChildren().add(new VBox(instructionText));

        return container;
    }

    private Parent createProfilerComponents()
    {
        VBox layout = new VBox();

        GridPane container = new GridPane();
        container.setPadding(new Insets(10));
        container.setHgap(4);
        container.setVgap(8);

        HBox threadCountContainer = new HBox();
        threadCountContainer.setSpacing(10);

        Text threadCountText = new Text("Threads: ");
        threadCountText.setStyle("-fx-font-size: 15px;");
        threadCountText.setTextAlignment(javafx.scene.text.TextAlignment.CENTER);

        threadCountField = new TextField("<null>");
        threadCountField.setStyle("-fx-font-size: 15px;");
        threadCountField.editableProperty().setValue(false);
        threadCountContainer.getChildren().add(threadCountText);
        threadCountContainer.getChildren().add(threadCountField);

        container.add(threadCountContainer, 0, 0);

        layout.getChildren().addAll(container, new Separator());

        return layout;
    }

    public GUIView(Interpreter newInterpreter, HardcodedProgramDB newProgramDB, Stage mainWindow) {
        interpreter = newInterpreter;
        programRepository = newProgramDB;

        window = mainWindow;
        window.setTitle("Select a Program");
        window.resizableProperty().setValue(false);
        window.setScene(new Scene(createSelectionContents(), 960, 960));
    }

    public void show() {
        window.show();
    }
}
