package com.Ghost.Interpreter.Repository;

import java.util.ArrayList;

import com.Ghost.Interpreter.Models.IValue;
import com.Ghost.Interpreter.Models.Types.RefferenceType;
import com.Ghost.Interpreter.Models.Values.RefferenceValue;

public class GarbageCollector {
    public static void collect(ProgramState state) {
        ArrayList<Integer> allocatedPositions = new ArrayList<Integer>();
        for(IValue variable : state.get_symbol_table().all().values())
            if(variable.get_type() instanceof RefferenceType) {
                RefferenceValue result = (RefferenceValue) variable;
                IValue resultValue = state.get_memory_heap().get(result.get_address());
                allocatedPositions.add(result.get_address());
                while(resultValue != null && resultValue.get_type() instanceof RefferenceType) {
                    result = (RefferenceValue)resultValue;
                    resultValue = state.get_memory_heap().get(result.get_address());
                    allocatedPositions.add(result.get_address());
                }
            }

        ArrayList<Integer> positionsToRemove = new ArrayList<Integer>();
        for(Integer variable : state.get_memory_heap().all().keySet())
            if(!allocatedPositions.contains(variable))
                positionsToRemove.add(variable);

        for(Integer position : positionsToRemove)
            state.get_memory_heap().remove(position);
    }
}
