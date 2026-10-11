import domain.MessageTask;
import domain.Task;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public void main(){
        //domain.Task t = new domain.Task("1", "test");
        //Nu se poate initializa, clasa abstracta

        MessageTask message = new MessageTask("1", "desc", "mesaj",
                "sender", "receiver", LocalDateTime.now());

        System.out.println(message);

        List<Task> list = new ArrayList<>();
        EmailTask email = new EmailTask("2", "descriere", "abcd@gmail.com");

        list.add(message);
        list.add(email);

        for(Task t : list){
            t.execute();
        }
    }

    private static void target(String title){
        System.out.printlm
    }
}
