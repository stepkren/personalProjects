package cz.cvut.fit.tjv.reservationdatabase.domain;

import jakarta.persistence.*;
import jakarta.validation.constraints.NotBlank;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.util.List;

@Entity
@Table(name = "Customer")
@Getter
@Setter // using lombok
@NoArgsConstructor
@AllArgsConstructor
public class Customer {
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE)
    @Column(name = "customer_id")
    private Long customerId;

    // Name of the customer, cannot be left blank
    @Column(name = "name", unique = true)
    @NotBlank
    private String name;

    // Phone number of the customer, cannot be left blank
    @Column(name = "phone_number")
    @NotBlank
    private String phoneNumber;

    // Email of the customer
    @Column(name = "email", nullable = true)
    private String email;

    // List of restaurants the customer visited, represented as a Many-To-Many relationship
    @ManyToMany(targetEntity = Restaurant.class)
    @JoinTable(
            name = "customer_restaurant_visited",
            joinColumns = @JoinColumn(name = "restaurant_id"),
            inverseJoinColumns = @JoinColumn(name = "customer_id")
    )
    private List<Restaurant> visited;
}
