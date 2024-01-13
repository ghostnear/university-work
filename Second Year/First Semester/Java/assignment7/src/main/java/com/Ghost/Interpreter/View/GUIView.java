package com.Ghost.Interpreter.View;

import java.util.ArrayList;

import com.Ghost.Interpreter.ADTs.Dictionary;
import com.Ghost.Interpreter.Controller.Interpreter;
import com.Ghost.Interpreter.Models.IStatement;
import com.Ghost.Interpreter.Models.IType;
import com.Ghost.Interpreter.Models.IValue;
import com.Ghost.Interpreter.Repository.HardcodedProgramDB;

import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.geometry.Insets;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonBar;
import javafx.scene.control.ButtonType;
import javafx.scene.control.ListView;
import javafx.scene.control.Separator;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.util.Pair;

public class GUIView extends IView {
    Stage window;
    HardcodedProgramDB programRepository;
    Interpreter interpreter;

    TextField threadCountField;
    ListView<String> outputField, fileTableField;
    ListView<Integer> threadListField;
    TableView<Pair<Integer, IValue>> heapTable;

    private void populateView()
    {
        final int thread_count = interpreter.get_program_states().size();

        // Update thread count.
        threadCountField.setText(String.valueOf(thread_count));

        // Update output.
        ObservableList<String> programOutputs = FXCollections.observableArrayList();
        for(String s : interpreter.get_output().split("\n"))
            programOutputs.add(s);
        outputField.setItems(programOutputs);
        outputField.editableProperty().set(false);

        // Update files.
        ObservableList<String> fileOutputs = FXCollections.observableArrayList();
        for(String s : interpreter.get_files())
            fileOutputs.add(s);
        fileTableField.setItems(fileOutputs);
        fileTableField.editableProperty().set(false);
        fileTableField.refresh();

        // Update thread IDs.
        ObservableList<Integer> threadIDs = FXCollections.observableArrayList();
        for(int i = 0; i < thread_count; i++)
            threadIDs.add(interpreter.get_program_states().get(i).get_id());
        threadListField.setItems(threadIDs);
        threadListField.editableProperty().set(false);
        if(threadListField.getSelectionModel().getSelectedItem() == null)
            threadListField.getSelectionModel().select(0);
        threadListField.refresh();

        // Stop here if no threads exist.
        if(thread_count == 0)
            return;

        // Update heap.
        TableColumn<Pair<Integer, IValue>, Integer> addressColumn = new TableColumn<Pair<Integer, IValue>, Integer>("Address");
        addressColumn.setCellValueFactory(p -> new SimpleIntegerProperty(p.getValue().getKey()).asObject());
        addressColumn.setPrefWidth(100);

        TableColumn<Pair<Integer, IValue>, String> valueColumn = new TableColumn<Pair<Integer, IValue>, String>("Value");
        valueColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getValue().toString()));
        valueColumn.setPrefWidth(320);
        valueColumn.setSortable(false);
        
        heapTable.getColumns().clear();
        heapTable.getColumns().addAll(addressColumn, valueColumn);
        
        heapTable.editableProperty().set(false);
        heapTable.getItems().clear();
        for(Pair<Integer, IValue> entry : interpreter.get_heap_all())
            heapTable.getItems().add(entry);
        heapTable.refresh();
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
                    interpreter.reset_program_state();
                    programs.get(finalIndex).typeCheck(new Dictionary<String, IType>());
                    interpreter.load_program(programs.get(finalIndex));
                    window.setScene(new Scene(createProfilerComponents(), 960, 960));
                    window.setTitle("Program Profiler");
                    populateView();
                } catch (Exception e) {
                    e.printStackTrace();
                    Alert alert = new Alert(Alert.AlertType.ERROR, e.toString(), ButtonType.OK);
                    alert.showAndWait();
                }
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

        Text instructionText = new Text("Press on any button to select a program.\nThis will replace the current window.");
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
        VBox.setVgrow(container, Priority.ALWAYS );
        container.setPadding(new Insets(10));
        container.setHgap(4);
        container.setVgap(8);

        VBox threadCountContainer = new VBox();
        Text threadCountText = new Text("Thread count: ");
        threadCountText.setTextAlignment(javafx.scene.text.TextAlignment.CENTER);

        threadCountField = new TextField("<null>");
        threadCountField.editableProperty().setValue(false);
        threadCountContainer.getChildren().add(threadCountText);
        threadCountContainer.getChildren().add(threadCountField);

        outputField = new ListView<String>();
        fileTableField = new ListView<String>();
        heapTable = new TableView<Pair<Integer, IValue>>();
        threadListField = new ListView<Integer>();

        container.add(threadCountContainer, 0, 0);
        container.add(new VBox(new Text("Output:"), outputField), 0, 2);
        container.add(new VBox(new Text("Files:"), fileTableField), 1, 2);
        container.add(new VBox(new Text("Heap:"), heapTable), 2, 2);
        container.add(new VBox(new Text("Threads:"), threadListField), 0, 3);

        ButtonBar buttonBar = new ButtonBar();
        buttonBar.setPadding(new Insets(10));

        Button advanceButton = new Button("Step once");
        advanceButton.setDefaultButton(true);
        advanceButton.onMouseClickedProperty().setValue((event) -> {
            try {
                interpreter.stepAll();
            } catch (Exception e) {
                e.printStackTrace();
                Alert alert = new Alert(Alert.AlertType.ERROR, e.toString(), ButtonType.OK);
                alert.showAndWait();
            }
            populateView();
        });

        Button backButton = new Button("Go back");
        backButton.onMouseClickedProperty().setValue((event) -> {
            initSelection();
        });

        buttonBar.getButtons().addAll(advanceButton, backButton);
        layout.getChildren().addAll(container, new Separator(), buttonBar);

        return layout;
    }

    private void initSelection()
    {
        window.setTitle("Select a Program");
        window.resizableProperty().setValue(false);
        window.setScene(new Scene(createSelectionContents(), 960, 960));
    }

    public GUIView(Interpreter newInterpreter, HardcodedProgramDB newProgramDB, Stage mainWindow) {
        interpreter = newInterpreter;
        programRepository = newProgramDB;

        window = mainWindow;
        initSelection();
    }

    public void show() {
        window.show();
    }
}
