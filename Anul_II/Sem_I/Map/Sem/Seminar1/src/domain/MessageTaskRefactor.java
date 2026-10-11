package domain;

public class MessageTaskRefactor extends Task {
    private final Message message;
    public MessageTaskRefactor(Message message) {
        super(message.getId(), message.getDescription());
        this.message = message;
    }
    @Override
    public void execute(){
        System.out.println("id:" + "Message:" + message.getMessage()); // de completat
    }
}
