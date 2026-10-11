package domain;

import java.time.LocalDateTime;

public class Message {
    private final String id;
    private final String description;
    private final String message;
    private final String from;
    private final String to;

    private final LocalDateTime date;
    public Message(String id, String description, String message, String from, String to, LocalDateTime date){
        this.id = id;
        this.description = description;
        this.message = message;
        this.from = from;
        this.to = to;
        this.date = date;
    }


    public LocalDateTime getDate() {
        return date;
    }

    public String getTo() {
        return to;
    }

    public String getFrom() {
        return from;
    }

    public String getMessage() {
        return message;
    }

    public String getDescription() {
        return description;
    }

    public String getId() {
        return id;
    }

}
