//
// Created by student on 01.06.2022.
//

#ifndef KOLEJEBILETY_REPOSITORY_H
#define KOLEJEBILETY_REPOSITORY_H
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <fstream>
#include <iostream>
#include "typedefs.h"

template <class T>
class Repository{
protected:
    std::vector<Ptr<T>> registry;
public:
    /**
     * Attempts to save the data on destruction.
     */
    ~Repository() {
        saveData();
    }

    /**
     * @return True if the sample ofstream is correctly opened and ready to write. False otherwise.
     */
    bool canSaveData() {
        return std::ofstream("data_perm_check").is_open();
    }

    /**
     * Attempts to save the data to an external file via <code>report</code>. <br>
     * Will return without success if <code>canSaveData</code> returns false or if the open stream returns true on <code>fail</code>.
     */
    void saveData() {
        if (!canSaveData()) {
            std::cerr << "Couldn't write data on exit (possible lack of permission)." << std::endl;
            return;
        }
        if (size() == 0) return;

        std::ostringstream path;
        path << "data_" << typeid(this).name() << "_";
        path << boost::uuids::random_generator()();
        path << ".txt";

        std::ofstream ofile(path.str());
        if (ofile.fail()) {
            std::cerr << "Couldn't write data on exit (failbit)." << std::endl;
            return;
        }

        ofile << report();
    }

    /**
     * Returns element by index. No-throw guarantee.
     * @return std::shared_ptr of element
     */
    Ptr<T> get(int index) noexcept {
        try{
            return registry.at(index);
        }
        catch (std::out_of_range & e){
            return nullptr;
        }
    }

    /**
     * Adds an element to the registry. If passed nullptr, nothing will change.
     * @param instance - std::shared_ptr of element
     */
    void add(Ptr<T> instance){
        if(instance== nullptr) return;
        registry.push_back(instance);
    }

    /**
     * Removes element from the registry. If passed nullptr, nothing will change.
     * @param instance - std::shared_ptr of element
     */
    void remove(Ptr<T> instance){
        if(instance== nullptr) return;
        registry.erase(std::remove(registry.begin(), registry.end(), instance),registry.end());
    }

    /**
     * @returns an array-like formatted report, including information about all contained elements.
     */
    std::string report() const {
        std::string info = "[";
        for(auto & curElem : registry)
            info += "(" + curElem->getInfo() + "), \n";
        info = info.substr(0,info.size()-3) + "]";
        return info;
    }

    /**
     * No-throw guarantee.
     * @returns a std::size_t size of the underlying registry.
     */
    size_t size() const noexcept{
        return registry.size();
    }


    /**
     * Finds elements by passed matching predicate.
     * @param matchingMethod - std::function-assignable predicate taking std::shared_ptr to find elements by.
     * @return std::vector with found elements, empty if found nothing.
     */
    std::vector<Ptr<T>> findBy(Predicate<Ptr<T>> matchingMethod) const {
        std::vector<Ptr<T>> found;
        for (auto & elem : registry) {
            if (elem != nullptr && matchingMethod(elem)) found.push_back(elem);
        }
        return found;
    }

    /**
     * @returns a vector of all contained elements.
     */
    std::vector<Ptr<T>> findAll() const {
        Predicate<Ptr<T>> f = [](const Ptr<T> & elem) -> bool { return true; };
        return findBy(f);
    }


    /**
     * Finds an element by id.
     * @tparam ID - id type of the element, usually std::string or boost::uuids::uuid
     * @return std::shared_ptr of the found element or nullptr if found nothing
     */
    template<class ID>
    Ptr<T> findById(ID id) const {
        Predicate<Ptr<T>> f = [id](const Ptr<T> & elem) -> bool {
            return elem->getID() == id;
        };
        auto found = findBy(f);
        return found.empty() ? nullptr : found[0];
    }

};
#endif //KOLEJEBILETY_REPOSITORY_H
