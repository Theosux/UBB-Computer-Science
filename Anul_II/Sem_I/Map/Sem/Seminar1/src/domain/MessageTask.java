package domain;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class MessageTask extends Task {
    private final String message;
    private final String from;
    private final String to;
    private final LocalDateTime date;
    public static final DateTimeFormatter DATE_TIME_FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM-dd hh:mm");

    public MessageTask(String taskID, String description, String message, String from, String to, LocalDateTime date) {
        super(taskID, description);
        this.message = message;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    @Override
    public void execute() {
        System.out.println("Mesaj:" + message + " blabla" + " From:" + from + " To:" + to + " Data:" + date.format(DATE_TIME_FORMATTER));
    }

    @Override
    public String toString() {
        return super.toString() + "Mesaj:" + message + " blabla" + " From:" + from + " To:" + to + " Data:" + date.format(DATE_TIME_FORMATTER);
    }
}
