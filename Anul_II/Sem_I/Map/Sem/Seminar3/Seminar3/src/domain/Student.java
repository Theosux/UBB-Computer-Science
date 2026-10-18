package domain;

import java.util.Objects;

public class Student extends Entity<Integer> implements Comparable<Student> {
    private String nume;
    private float media;

    public Student(String nume, float media) {
        super(id);
        this.nume = nume;
        this.media = media;
    }


    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public float getMedia() {
        return media;
    }

    public void setMedia(float media) {
        this.media = media;
    }

    @Override
    public String toString() {
        return "Student: " + nume + " Medie: " + media;
    }

    @Override
    public boolean equals(Object o) {
        if(this == o) {
            return true;
        }
        if (o == null || o.getClass() != this.getClass()) {
            return false;
        }
        return Float.compare(this.media, ((Student) o).media) == 0 && Objects.equals(this.nume, ((Student) o).nume);
    }

    @Override
    public int hashCode() {
        return Objects.hash(nume, media);
    }

    @Override
    public int compareTo(Student s) {
        return nume.compareTo(s.nume);
    }
}
