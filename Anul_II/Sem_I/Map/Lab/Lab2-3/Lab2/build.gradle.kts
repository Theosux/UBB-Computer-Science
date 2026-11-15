plugins {
    id("java")
}

repositories {
    mavenCentral()
}

dependencies {
    // driverul JDBC pentru PostgreSQL
    implementation("org.postgresql:postgresql:42.7.7")
}