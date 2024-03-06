package cz.cvut.fit.tjv.reservationdatabase.domain;

import jakarta.persistence.*;
import jakarta.validation.constraints.NotBlank;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.util.List;
import java.util.Date;


@Entity
@Table(name = "Restaurant")
@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class Restaurant {
    // Primary key for the restaurant entity instance
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE)
    @Column(name = "restaurant_id")
    private Long restaurantId;

    // Name of the restaurant, cannot be left blank
    @Column(name = "name", unique = true)
    @NotBlank
    private String name;

    // Phone number of the restaurant, cannot be left blank
    @Column(name = "phone_number")
    @NotBlank
    private String phoneNumber;

    // Date when the restaurant first opened, cannot be left blank
    @Column(name = "open_from")
    private Date openFrom;

    // Number of items on the menu of the restaurant
    @Column(name = "items_on_menu")
    private Long itemsOnMenu;

    // Cuisine that the restaurant cooks, represented as a Many-To-One relationship
    @ManyToOne(targetEntity = Cuisine.class)
    @JoinColumn(name = "cooked_at")
    private Cuisine cooks;

    // List of customers who have visited the restaurant, represented as a Many-To-Many relationship
    @ManyToMany(mappedBy = "visited")
    private List<Customer> visitedBy;
}
