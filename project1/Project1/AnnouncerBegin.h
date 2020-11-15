/**
 * \file AnnouncerBegin.h
 *
 * \author Jonathan Lee
 *
 * Begin message class that displays before levels begin
 */

#pragma once
#include "Announcer.h"

 /** Class that displays Announcements before level */
class CAnnouncerBegin : public CAnnouncer
{
public:
    /// Default constructor disabled
    CAnnouncerBegin() = delete;

    /// Copy Constructor
    CAnnouncerBegin(const CAnnouncerBegin&) = delete;

    /// Destructor
    ~CAnnouncerBegin();

    CAnnouncerBegin(CTowerGame* towerGame);

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitAnnouncer(this); }

    virtual void Draw(Gdiplus::Graphics* graphics) override;

    virtual void Update(double elapsed) override;

private:
    /// Time left till deletion
    double mTimeTillDelete = 4;

    /// bool to know when to delete announcement
    bool mDelete = false;
};

