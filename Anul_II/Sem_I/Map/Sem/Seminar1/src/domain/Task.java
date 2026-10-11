package domain;

import java.util.Objects;

//Clasa ne descrie un concept incomplet si nu poate fi instantiata
public abstract class Task {
    private String taskID;
    private String description;

    //Constructor ce initializeaza partea comuna a oricarui domain.Task complet
    public Task(String taskID, String description) {
        this.taskID = taskID;
        this.description = description;
    }

    public String getTaskID(){
        return this.taskID;
    }

    public String getDescription(){
        return this.description;
    }

    public void setTaskID(String taskID){
        this.taskID = taskID;
    }

    public void setDescription(String description){
        this.description = description;
    }

    //Metoda abstracta va fi suprascrisa si va executa conform clasei mostenitoare
    public abstract void execute();

    @Override
    public String toString() {
        return "ID:" + taskID + ' ' + " Description:" + description;
    }

    @Override
    public boolean equals(Object o){
        //Daca e aceeasi instanta returneaza true
        if (this == o) return true;
        //Verifica daca obiectul este valid si verificam daca obiectele sunt de acelasi tip
        if (o == null || getClass() != o.getClass()) return false;
        //Se converteste obiectul in domain.Task si se verifica egalitatea dintre taskID a celor doua obiecte
        Task task = (Task) o;
        return Objects.equals(task.taskID, this.taskID);
    }

    @Override
    public int hashCode() {
        //Generam hashCode cu functia folosita pentru egalitate
        return Objects.hash(taskID);
    }

}
