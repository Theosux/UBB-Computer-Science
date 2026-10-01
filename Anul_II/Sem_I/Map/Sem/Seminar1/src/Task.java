import java.util.List;
import java.util.Objects;



public abstract class Task {
    private String taskID;
    private String description;

    //Constructor
    public Task(String taskId, String description) {
        this.taskID = taskID;
        this.description = description;
    }
    public abstract void execute();

    public String toString() {
        return taskID + ' ' + description;
    }

    @Override
    public boolean equals(Object obj){
        //Daca e acelasi obiect returneaza true
        if (this == obj) return true;
        //Daca este obiectul valid sau nu || si verificam daca obiectele sunt de acelasi tip
        if (obj == null || getClass() != obj.getClass()) return false;
        //cast(conversie) obiect in Task si se verifica egalitatea dintre taskID a celor doua obiecte
        Task task = (Task) obj;
        return Objects.equals(task.taskID, this.taskID);
    }

    @Override
    public int hashCode() {
        //Generam un hashCode cu functia folosita pt egalitate
        return Objects.hash(taskID);
    }
}
