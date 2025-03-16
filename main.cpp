#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Note {
    int id;
    std::string content;
};

std::vector<Note> loadNotes() {
    std::vector<Note> notes;
    std::ifstream file("notes.txt");
    Note note;
    while (file >> note.id) {
        file.ignore();
        std::getline(file, note.content);
        notes.push_back(note);
    }
    return notes;
}

void saveNotes(const std::vector<Note>& notes) {
    std::ofstream file("notes.txt");
    for (const auto& note : notes) {
        file << note.id << " " << note.content << std::endl;
    }
}

void addNote() {
    std::vector<Note> notes = loadNotes();
    Note newNote;
    newNote.id = notes.empty() ? 1 : notes.back().id + 1;

    std::cout << "Masukkan catatan: ";
    std::cin.ignore();
    std::getline(std::cin, newNote.content);

    notes.push_back(newNote);
    saveNotes(notes);
    std::cout << "Catatan berhasil ditambahkan!\n";
}

void viewNotes() {
    std::vector<Note> notes = loadNotes();
    if (notes.empty()) {
        std::cout << "Tidak ada catatan.\n";
        return;
    }
    for (const auto& note : notes) {
        std::cout << note.id << ". " << note.content << std::endl;
    }
}

void editNote() {
    std::vector<Note> notes = loadNotes();
    int id;
    std::cout << "Masukkan ID catatan yang ingin diedit: ";
    std::cin >> id;
    std::cin.ignore();

    for (auto& note : notes) {
        if (note.id == id) {
            std::cout << "Masukkan catatan baru: ";
            std::getline(std::cin, note.content);
            saveNotes(notes);
            std::cout << "Catatan berhasil diperbarui!\n";
            return;
        }
    }
    std::cout << "Catatan tidak ditemukan.\n";
}

void deleteNote() {
    std::vector<Note> notes = loadNotes();
    int id;
    std::cout << "Masukkan ID catatan yang ingin dihapus: ";
    std::cin >> id;

    std::vector<Note> newNotes;
    bool found = false;
    for (const auto& note : notes) {
        if (note.id == id) {
            found = true;
        } else {
            newNotes.push_back(note);
        }
    }

    if (found) {
        saveNotes(newNotes);
        std::cout << "Catatan berhasil dihapus!\n";
    } else {
        std::cout << "Catatan tidak ditemukan.\n";
    }
}

int main() {
    int choice;
    do {
        std::cout << "\n=== Aplikasi Catatan ===\n";
        std::cout << "1. Tambah Catatan\n";
        std::cout << "2. Lihat Catatan\n";
        std::cout << "3. Edit Catatan\n";
        std::cout << "4. Hapus Catatan\n";
        std::cout << "5. Keluar\n";
        std::cout << "Pilihan: ";
        std::cin >> choice;

        switch (choice) {
            case 1: addNote(); break;
            case 2: viewNotes(); break;
            case 3: editNote(); break;
            case 4: deleteNote(); break;
            case 5: std::cout << "Keluar...\n"; break;
            default: std::cout << "Pilihan tidak valid.\n";
        }
    } while (choice != 5);

    return 0;
}
