import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public void main(){

        MessageTask message = new MessageTask( taskID: "1", description: "desc", message: "mesaj", from: "sender", to:"receiver", LocalDateTime.now());

        System.out.println(message);

        List<Task> list = new ArrayList<>();
        EmailTask email = new EmailTask( taskID: "2", description: "descriere", email: "abcd@gmail.com");
        list.add(message);
        list.add(email);

        for(Task t : list){
            t.execute();
        }
    }
}