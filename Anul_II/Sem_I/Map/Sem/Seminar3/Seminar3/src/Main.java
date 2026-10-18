import domain.Student;
import map.MyMap;
import repository.InMemoryRepository;

import java.util.*;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args){
        Student s1 = new Student("Dan", 4.5f);
        Student s2 = new Student("Ana", 8.5f);
        Student s3 = new Student("Dan", 4.5f);

//        System.out.println(s1);
//        System.out.println(s2);
//        System.out.println(s3);

        HashSet<Student> hashSet = new HashSet<>();
//        hashSet.add(s1);
//        hashSet.add(s2);
//        hashSet.add(s3);

        Collections.addAll(hashSet, s1, s2, s3);
        for (Student s : hashSet) {
            System.out.println(s);
        }

        System.out.println("s1 == s3" + (s1  == s3));
        System.out.println("s1 == s3" + (s1.equals(s3)));
        System.out.println("s1.hashCode() == s3.hashCode()" + (s1.hashCode() == s3.hashCode()));
        System.out.println(hashSet.size());

        System.out.println("Tree set:");
        TreeSet<Student> treeSet = new TreeSet<>(Comparator.comparing(Student::getNume));
        Collections.addAll(treeSet, s1, s2, s3);
        System.out.println(treeSet);

        HashMap<Student, String> hashMap = new HashMap<>();
        hashMap.put(s1, "Dan1");
        hashMap.put(s2, "Ana");
        hashMap.put(s3, "Dan2");

        System.out.println("Hashmap: " + hashMap.size() + " " + hashMap);

        TreeMap<Student, String> treeMap = new TreeMap<>(Comparator.comparing(Student::getNume));
        treeMap.put(s1, "Dan1");
        treeMap.put(s2, "Ana");
        treeMap.put(s3, "Dan2");

        System.out.println("Treemap: " + treeMap.size() + " " + treeMap);

        MyMap map = new MyMap();

        for (Student s : getList()) {
            map.add(s);
        }

        for (Map.Entry<Integer, List<Student>> entry : map.getEntries()) {
            List<Student> students = new ArrayList<>(entry.getValue());
            students.sort(Comparator.comparing(Student::getNume));
            System.out.println("Media Rotunjita: " + entry.getKey() + " " + students);
        }

        InMemoryRepository<Integer, Student> repo = new InMemoryRepository<Integer, Student>()
    }

    public static List<Student> getList() {
        List<Student> l = new ArrayList<Student>();
        l.add(new Student("1", 9.7f));
        l.add(new Student("2", 7.3f));
        l.add(new Student("3", 6f));
        l.add(new Student("4", 6.9f));
        l.add(new Student("5", 9.5f));
        l.add(new Student("6", 9.9f));
        return l;
    }
}